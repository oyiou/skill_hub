//
// Created by leever on 2023/4/21.
//
#include "opengl_programing_guide.h"

GLuint sampler; // 这个变量保存采样器的名称
GLuint texture; // 这个变量保存纹理的名称
const GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f}; // 不透明红色
// 采样器对象设置
glSamplerParameterfv(sampler, GL_TEXTURE_BORDER_COLOR, red);
// 或者为纹理对象设置边界颜色
// 如果纹理绑定到没有对应采样器对象的纹理单元，那么将使用这一方法
glBindTexture(GL_TEXTURE_2D, texture);
glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, red);