//
// Created by leever on 2023/4/21.
//
#include "opengl_programing_guide.h"

GLuint tex; // 创建纹理
extern const GLvoid *texture_data[6];   // 用于表面的数据
// 使用 GL_TEXTURE_CUBE_MAP 目标生成、绑定和初始化纹理对象
glGenTextures(1, &tex);
glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
glTexStorage2D(GL_TEXTURE_CUBE_MAP, 10, GL_RGBA8, 1024, 1024);
// 既然为纹理对象分配了存储空间，则可以把纹理数据放进纹素数组
for (int face = 0; face < 6; face++) {
    GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;
    glTexSubImage2D(target,                 // 面目标
                    0,                      // 级别
                    0, 0,                   // X、Y 偏移
                    1024, 1024,             // 面的大小
                    GL_RGBA,                // 格式
                    GL_UNSIGNED_BYTE,       // 类型
                    texture_data[face]);    // 数据
}
// 有必要，也可以为每个面的低层级 mipmap 设置数据