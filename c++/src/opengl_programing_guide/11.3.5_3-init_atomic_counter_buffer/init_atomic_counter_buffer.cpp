//
// Created by leever on 2023/5/10.
//
#include "opengl_programing_guide.h"

// 局部变量
GLuint buffer;
GLuint *counters;

// 生成缓存的名称，将名称绑定到 GL_ATOMIC_COUNTER_BUFFER 绑定点，这样就可以创建这个缓存对象了
glGenBuffers(1, &buffer);
glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, buffer);

// 在缓存中分配两个 GLuint 的大小即可
glBufferData(GL_ATOMIC_COUNTER_BUFFER, 2 * sizeof(GLuint), NULL, GL_DYNAMIC_COPY);

// 现在映射缓存并初始化它的数据
counters = (GLuint*)glMapBuffer(GL_ATOMIC_COUNTER_BUFFER, GL_MAP_WRITE_BIT);

counters[0] = 0;
counters[1] = 0;
glUnmapBuffer(GL_ATOMIC_COUNTER_BUFFER);

// 最后，将初始化之后的缓存绑定到 GL_ATOMIC_COUNTER_BUFFER 的索引 0 位置
glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, buffer);