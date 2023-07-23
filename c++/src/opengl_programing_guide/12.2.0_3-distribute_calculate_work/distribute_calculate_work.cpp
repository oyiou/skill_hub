//
// Created by leever on 2023/5/10.
//
#include "opengl_programing_guide.h"

// program 是一个已经成功链接的程序对象，其中包含计算着色器
GLuint program;

// 启用程序对象
glUseProgram(program);

// 创建缓存，将它绑定给 DISPATCH_INDIRECT_BUFFER 绑定点，并填充数据
glGenBuffers(1, &dispatch_buffer);
glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, dispatch_buffer);

static const struct {
    GLuint num_groups_x;
    GLuint num_groups_y;
    GLuint num_groups_z;
}; dispatch_params = {16, 16, 1};

glBufferData(GL_DISPATCH_INDIRECT_BUFFER,
            sizeof(dispatch_params),
            &dispatch_params,
            GL_STATIC_DRAW);

// 使用缓存对象中填充的参数来分发计算着色器
glDispatchComputeIndirect(0);