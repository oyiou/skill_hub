//
// Created by leever on 2023/4/23.
//
#include "opengl_programing_guide.h"

// 创建两个纹理名，一个是原始纹理，另一个是视图
GLuint tex[2];
glGenTexture(2, &tex);
// 绑定第一个纹理，初始化它的数据存储，准备创建一个 100 层的二维数组纹理，每层大小为 256x256
glBindTexture(GL_TEXTURE_2D_ARRAY, tex[0]);
glTexStorage3D(GL_TEXTURE_2D_ARRAY, 8, GL_RGBA32F, 256, 256, 100);
// 创建纹理的 GL_TEXTURE_2D 视图，从纹理中提取出一个切片
glTextureView(tex[1],           // 新纹理视图
              GL_TEXTURE_2D,    // 新视图的目标
              tex[0],           // 初始纹理
              GL_RGBA32F,       // 与初始纹理相同的格式
              0, 8,             // 所有的 mipmaps
              50, 1);           // 只有一层