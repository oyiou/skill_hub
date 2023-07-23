//
// Created by leever on 2023/4/23.
//
#include "opengl_programing_guide.h"

// 用作数据存储的缓存
GLuint buf;
// 用作缓存纹理的纹理
GLuint tex;
// 数据在程序中其他地方
extern const GLvoid *data;
// 使用 GL_TEXTURE_BUFFER 绑定来生成、绑定和初始化对象。假设在这里使用 1MB 数据
glGenBuffers(1, &buf);
glBindBuffer(GL_TEXTURE_BUFFER, buf);
glBufferData(GL_TEXTURE_BUFFER, 1024 * 1024, data, GL_STATIC_DRAW);
// 创建缓存纹理，把它与缓存对象关联
glGenTextures(1, &tex);
glBindTexture(GL_TEXTURE_BUFFER, tex);
glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, buf);