//
// Created by leever on 2023/4/14.
//
#include "opengl_programing_guide.h"

// 首先绑定缓存到 GL_PIXEL_UNPACK_BUFFER
glBindBuffer(GL_PIXEL_UNPACK_BUFFER, buf);
// 把源数据放进缓存
glBufferData(GL_PIXEL_UNPACK_BUFFER,
             sizeof(tex_checkerboard_data),
             tex_checkerboard_data,
             GL_STATIC_DRAW
             );
// 绑定纹理、也可能是创建纹理
glBindTexture(GL_TEXTURE_2D, tex_checkerboard);
// 为纹理数据分配存储
glTexStorage2D(GL_TEXTURE_2D, 4, GL_R8, 8, 8);
// 为纹理设置数据
glTexSubImage2D(GL_TEXTURE_2D,      // 目标
                0,                  // 第一个 mipmap 级
                0, 0,               // x、y 偏移
                8, 8,               // 宽度和高度
                GL_RED,             // 格式
                GL_UNSIGNED_BYTE,   // 类型
                NULL                // 数据（缓存里的偏移）
                );