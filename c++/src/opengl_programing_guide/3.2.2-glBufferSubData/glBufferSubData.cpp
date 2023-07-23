//
// Created by leever on 2023/3/28.
//
#include "opengl_programing_guide.h"

// 顶点位置
static const GLfloat positions[] = {
        -1.0f,  -1.0f,  0.0f,   1.0f,
        1.0f,  -1.0f,  0.0f,   1.0f,
        1.0f,  1.0f,  0.0f,   1.0f,
        -1.0f,  1.0f,  0.0f,   1.0f,
};

// 顶点颜色
static const GLfloat colors[] = {
        1.0f,   0.0f,   0.0f,
        0.0f,   1.0f,   0.0f,
        0.0f,   0.0f,   1.0f,
        1.0f,   1.0f,   1.0f,
};

// 缓存对象
GLuint buffer;

// 为缓存对象生成一个名称
glGenBuffers(1, &buffer);
// 将它绑定到 GL_ARRAY_BUFFER 目标
glBindBuffer(GL_ARRAY_BUFFER, buffer);
// 分配足够的空间 (sizeof(positions) + sizeof(colors))
glBufferData(GL_ARRAY_BUFFER,                       // 目标
             sizeof(positions) + sizeof(colors),    // 总计大小
             NULL,                                  // 无数据
             GL_STATIC_DRAW                         // 用途
             );
// 将位置信息放置在缓存的偏移地址为 0 的位置
glBufferSubData(GL_ARRAY_BUFFER,        // 目标
                0,                      // 偏移地址
                sizeof(positions),      // 大小
                positions               // 数据
                );
// 放置在缓存中的颜色信息的偏移地址为当前填充大小值的位置，也就是 sizeof(positions)
glBufferSubData(GL_ARRAY_BUFFER,        // 目标
                sizeof(positions),      // 偏移地址
                sizeof(colors),         // 大小
                colors                  // 数据
                );
// 现在位置信息位于偏移 0，而颜色信息保存在同一缓存中，紧随其后