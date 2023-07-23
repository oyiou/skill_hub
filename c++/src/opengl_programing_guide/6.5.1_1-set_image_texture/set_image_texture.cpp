//
// Created by leever on 2023/4/14.
//
#include "opengl_programing_guide.h"

// 下面使用 GL_RED、GL_UNSIGNED_BYTE 数据的 8x8 棋盘格图案
static const GLubyte tex_checkerboard_data[] = {
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
        0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
};
// 下面是用 GL_RGBA、GL_FLOAT 数据表示红、绿、蓝，黄组成的 2x2 纹理
static const GLfloat tex_color_data[] = {
        // 红色和绿色纹素                              Green texel
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        // 蓝色和黄色纹素                              Yellow texel
        0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};