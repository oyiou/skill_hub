//
// Created by leever on 2023/4/21.
//
#include "opengl_programing_guide.h"

GLuint tex; // 创建纹理

extern const GLvoid * texture_data[6][5];   // 面的数据
// 使用 GL_TEXTURE_CUBE_MAP_ARRAY 目标来创建、绑定和初始化纹理对象
glGenTextures(1, &tex);
glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, tex);
glTexStorage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 10, GL_RGBA8, 1024, 1024, 5);
// 既然已经为纹理对象分配了存储，则可以把纹理数据放进纹素数组
for (int cube_index = 0; cube_index < 5; cube_index++) {
    for (int face = 0; face < 6; face++) {
        GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;
        glTexSubImage3D(target,                             // 面目标
                        0,                                  // 级别
                        0, 0,                               // 偏移
                        cube_index,                         // 立方体映射索引
                        1024, 1024,                         // 宽、高
                        1,                                  // 面数
                        GL_RGBA,                            // 格式
                        GL_UNSIGNED_BYTE,                   // 类型
                        texture_data[face][cube_index]);    // 数据
    }
}