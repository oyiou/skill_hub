//
// Created by leever on 2023/4/23.
//
#include "opengl_programing_guide.h"

// 创建两个纹理名，一个用于原始数据，另一个用于视图
GLuint tex[2];
glGenTextures(2, &tex);
// 这里绑定第一个纹理并且初始化它的数据存储，存储是 1024x1024 的二维纹理，带有 mipmaps，格式是 GL_RGB8 —— 每个分量是 8 位，无符号归一化
glBindTexture(GL_TEXTURE_2D, tex[0]);
glTexStorage2D(GL_TEXTURE_2D, 10, GL_RGB8, 1024, 1024);
// 现在创建纹理视图，这时使用 GL_RGB8UI 来从纹理获取原始数据
glTextureView(tex[1],           // 新纹理视图
              GL_TEXTURE_2D,    // 新视图的目标
              tex[0],           // 原始纹理
              GL_RGB8UI,        // 新格式
              0, 10,            // 所有的 mipmaps
              0, 1);            // 只有一层