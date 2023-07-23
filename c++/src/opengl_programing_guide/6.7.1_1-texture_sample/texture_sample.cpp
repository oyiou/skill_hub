//
// Created by leever on 2023/4/21.
//
#include "opengl_programing_guide.h"

// prog 包括示例顶点和片元着色器链接程序的名称
glUseProgram(prog);
// tex 已经使用一些纹理数据来初始化纹理对象的名称
glBindTexture(GL_TEXTURE_2D, tex);
// 带纹理坐标的简单四边形
static const GLfloat quad_data[] = {
        // 顶点位置
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,
        // 纹理坐标
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
};
// 创建并且初始化一个缓存对象
GLuint buf;
glGenBuffers(1, &buf);
glBindBuffer(GL_ARRAY_BUFFER, buf);
glBufferData(GL_ARRAY_BUFFER, quad_data, sizeof(quad_data), GL_STATIC_DRAW);
// 设置顶点属性
GLuint vao;
glGenVertexArrays(1, &vao);
glBindVertexArray(vao);
glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(16*sizeof(float)));
glEnableVertexAttribArray(1);
// 已经准备好绘制
glDrawArrays(GL_TRIANGLE_FAN, 0, 4);