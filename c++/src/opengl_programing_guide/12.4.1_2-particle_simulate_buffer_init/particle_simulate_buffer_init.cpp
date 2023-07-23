//
// Created by leever on 2023/5/11.
//
#include "opengl_programing_guide.h"

// 生成两个缓存，绑定并初始化数据
glGenBuffers(2, buffers);
glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
glBufferData(GL_ARRAY_BUFFER,
             PARTICLE_COUNT * sizeof(vmath::vec4),
             NULL,
             GL_DYNAMIC_COPY);

// 映射位置缓存并且使用随机向量填充
vmath::vec4 *positions = (vmath::vec4 *)glMapBufferRange(GL_ARRAY_BUFFER,
                                                         0,
                                                         PARTICLE_COUNT * sizeof(vmath::vec4),
                                                         GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
for (i = 0; i < PARTICLE_COUNT; i++) {
    positions[i] = vmath::vec4(random_vector(-10.0f, 10.0f), random_float());
}

glUnmapBuffer(GL_ARRAY_BUFFER);

// 初始化速度缓存——同样使用随机向量填充
glBindBuffer(GL_ARRAY_BUFFER, velocity_buffer);
glBufferData(GL_ARRAY_BUFFER,
             PARTICLE_COUNT * sizeof(vmath::vec4),
             NULL,
             GL_DYNAMIC_COPY);

vmath::vec4 *velocities = (vmath::vec4 *)glMapBufferRange(GL_ARRAY_BUFFER,
                                                          0,
                                                          PARTICLE_COUNT * sizeof(vmath::vec4),
                                                          GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

for (i = 0; i < PARTICLE_COUNT; i++) {
    velocities[i] = vmath::vec4(random_vector(-0.1f, 0.1f), 0.0f);
}

glUnmapBuffer(GL_ARRAY_BUFFER);