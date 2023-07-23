//
// Created by leever on 2023/4/14.
//
#include "opengl_programing_guide.h"

// 首先是黑白棋盘纹理绑定纹理（也可能创建纹理）
glBindTexture(GL_TEXTURE_2D, tex_checkerboard);
// 位纹理数据分配存储
glTexStorage2D(GL_TEXTURE_2D, 4, GL_R8, 8, 8);
// 为纹理设置数据
glTexSubImage2D(GL_TEXTURE_2D,              // 目标
                0,                          // 第一个 mipmap 级数
                0, 0,                       // x、y 偏移
                8, 8,                       // 宽度和高度
                GL_RED, GL_UNSIGNED_BYTE,   // 格式和类型
                tex_checkerboard_data       // 数据
                );
// 加下来，浮点数的颜色纹理绑定下一个纹理
glBindTexture(GL_TEXTURE_2D, tex_color);
// 分配存储
glTexStorage2D(GL_TEXTURE_2D, 2, GL_RGBA32F, 2, 2);
// 设置数据
glTexSubImage(GL_TEXTURE_2D,              // 目标
              0,                          // 第一个 mipmap 级数
              0, 0,                       // x、y 偏移
              8, 8,                       // 宽度和高度
              GL_RED, GL_UNSIGNED_BYTE,   // 格式和类型
              tex_checkerboard_data       // 数据
);