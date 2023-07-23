//
// Created by leever on 2023/3/29.
//
#include "opengl_programing_guide.h"

// 四个顶点
static const GLfloat vertex_positions[] = {
        -1.0f,  -1.0f,  0.0f,   1.0f,
        1.0f,  -1.0f,  0.0f,   1.0f,
        -1.0f,  1.0f,  0.0f,   1.0f,
        -1.0f,  -1.0f,  0.0f,   1.0f,
};
// 每个顶点的颜色
static const GLfloat vertex_colors[] = {
        1.0f,  1.0f,  1.0f,   1.0f,
        -1.0f,  1.0f,  0.0f,   1.0f,
        -1.0f,  0.0f,  1.0f,   1.0f,
        0.0f,  1.0f,  1.0f,   1.0f,
};
// 三个索引值（这次只绘制一个三角形）
static const GLushort vertex_indices[] = {
        0, 1, 2
};
// 设置元素数组缓存
glGenBuffers(1, ebo);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices), vertex_indices, GL_STATIC_DRAW);
// 设置顶点属性
glGenVertexArrays(1, vao);
glBindVertexArray(vao[0]);

glGenBuffers(1, vbo);
glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions) + sizeof(vertex_colors), NULL, GL_STATIC_DRAW);
glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex_positions), vertex_positions);
glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex_positions), sizeof(vertex_colors), vertex_colors);