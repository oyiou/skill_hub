//
// Created by leever on 2023/5/11.
//
#include "opengl_programing_guide.h"

// 更新引力器位置和质量的缓存
vmath::vec4 *attractors = (vmath::vec4 *)glMapBufferRange(GL_UNIFORM_BUFFER,
                                                          0,
                                                          32 * sizeof(vmath::vec4),
                                                          GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

int i;

for (i = 0; i < 32; i++) {
    attractors[i] = vmath::vec4(sinf(time * (float )(i + 4) * 7.5f * 10.0f) * 50.0f,
                                conf(time * (float )(i + 7) * 3.9f * 20.0f) * 50.0f,
                                sinf(time * (float )(i + 3) * 5.3f * 20.0f) * cosf(time * (float )(i + 5) * 9.1f) * 100.0f,
                                attractor_masses[i]);
}

glUnmapBuffer(GL_UNIFORM_BUFFER);

// 激活计算着色器程序、绑定位置和速度缓存
glUseProgram(compute_prog);
glBindImageTexture(0, velocity_tbo, 0,
                   GL_FALSE, 0,
                   GL_READ_WRITE, GL_RGBA32F);
glBindImageTexture(1, position_tbo, 0,
                   GL_FALSE, 0,
                   GL_READ_WRITE, GL_RGBA32F);

// 设置时间间隔
glUniform1f(dt_location, delta_time);

// 执行计算着色器
glDispatchCompute(PARTICLE_GROUP_COUNT, 1, 1);

// 确保计算着色器的写入操作已经完成
glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

// 设置模型视图投影矩阵
vmath::mat4 mvp = vmath::perspective(45.0f, aspect_ratio, 1.0f, 1000.0f) *
                    vmath::translate(0.0f, 0.0f, -60.0f) *
                    vmath::rotate(time * 1000.0f, vmath::vec3(0.0f, 1.0f, 0.0f));

// 清除缓存，选择渲染程序，绘制全屏幕的四边形
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glUseProgram(render_prog);
glUniformMatrix4fv(0, 1, GL_FALSE, mvp);
glBindVertexArray(render_vao);
glEnable(GL_BLEND);
glBlendFunc(GL_ONE, GL_ONE);
glDrawArrays(GL_POINTS, 0, PARTICLE_COUNT);