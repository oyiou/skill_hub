//
// Created by leever on 2023/4/28.
//
#include "opengl_programing_guide.h"

// 随着时间变化的光源位置
vec3 liight_position = vec3(
        sinf(t * 6.0f * 3.141592f) * 300.0f,
        200.0f,
        cosf(t * 4.0f * 3.141592f) * 100.0f + 250.0f
        );
// 渲染场景所用的矩阵
mat4 scene_model_matrix = rotate(t * 720.0f, Y);
// 从光源位置渲染所用的矩阵
mat4 light_view_matrix = lookat(light_position, vec3(0.0f), Y);
mat4 light_projection_matrix(frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, FRUSTUM_DEPTH));
// 现在从光源位置渲染到深度缓存中。选择对应的着色器程序
glUseProgram(render_light_prog);
glUniformMatrix4fv(render_light_uniforms.MVPMatrix,
                   1, GL_FALSE,
                   light_projection_matrix * light_view_matrix * scene_model_matrix);