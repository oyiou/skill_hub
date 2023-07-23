//
// Created by leever on 2023/5/9.
//
#include "opengl_programing_guide.h"

GLuint buf;

// 生成缓存名称，创建并绑定到存储缓存
glGenBuffers(1, &buf);
glBindBuffer(GL_SHADER_STORAGE_BUFFER, buf);
glBufferData(GL_SHADER_STORAGE_BUFFER, 8192, NULL, GL_DYNAMIC_COPY);

// 现在将缓存绑定到第 0 个 GL_SHADER_STORAGE_BUFFER 绑定点
glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buf);