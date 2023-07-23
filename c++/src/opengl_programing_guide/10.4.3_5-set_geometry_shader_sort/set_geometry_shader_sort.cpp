//
// Created by leever on 2023/5/9.
//
#include "opengl_programing_guide.h"

// 创建两个顶点数组对象和缓存对象，用于保存中间数据
glGenVertexArrays(1, vao);
glGenBuffers(2, vbo);

// 根据 transform feedback 操作的情况创建一个 transform feedback 对象（包括后继的缓存绑定），然后对它进行绑定
glGenTransformFeedbacks(1, &xfb);
glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, xfb);

// 对于两个输出数据流
for (i = 0; i < 2; i++) {
    // 绑定缓存对象，继而创建对象
    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, vbo[i]);
    // 调用 glBufferData 来分配空间。GL_DYNAMIC_COPY 表示数据的变化频繁（DYNAMIC），并且会同时被 GPU 执行读取和写入的操作（COPY）
    glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, 1024 * 1024 * sizeof(GLfloat), NULL, GL_DYNAMIC_COPY);
    // 现在将它绑定到与数据流对应的 transform feedback 缓存绑定点
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, i, vbo[i]);

    // 设置 VAO，首先创建它
    glBindVertexArray(vao[i]);
    // 绑定 VBO 到 ARRAY_BUFFER 绑定点
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
    // 设置位置和法线的顶点属性...
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vec4) + sizeof(vec3), (GLvoid *)(sizeof(vec4)));
    // 并且不要忘了开启它们
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}