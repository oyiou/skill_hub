//
// Created by leever on 2023/3/29.
//
#include "opengl_programing_guide.h"

// 获取顶点属性在 prog 当中的位置，prog 就是准备用于渲染的着色器程序对象
// 注意，这一步并不是必需的，因为已经在顶点着色器中设置了所有属性的位置
// 这里的代码可以编写的更简单一些，只需要直接给出程序中已经设置了属性位置即可

int position_loc    = glGetAttribLocation(prog, "position");
int normal_loc      = glGetAttribLocation(prog, "normal");
int color_loc       = glGetAttribLocation(prog, "color");
int matrix_loc      = glGetAttribLocation(prog, "model_matrix");

// 配置正规的顶点属性数组——顶点和法线
glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
glVertexAttribPointer(position_loc, 4, GL_FLOAT, GL_FALSE, 0, NULL);
glEnableVertexAttribArray(position_loc);
glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
glEnableVertexAttribArray(normal_loc);

// 设置颜色的数组。希望几何体的每个实例都有一个不同的颜色，因此直接将颜色值置入缓存对象中，然后设置一个实例化的顶点属性
glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
glVertexAttribPointer(color_loc, 4, GL_FLOAT, GL_FALSE, 0, NULL);
glEnableVertexAttribArray(color_loc);
// 这里的设置很重要...设置颜色数组的更新频率为 1，那么 OpenGL 会给每个实例设置一个新的颜色值，而不是每个顶点的设置了
glVertexAttribDivisor(color_loc, 1);

// 与之类似，给模型矩阵也做同样的设置。注意输入到顶点着色器的矩阵会占据 N 个连续的输入位置，其中 N 表示矩阵的列数。因此...等于设置了四个顶点属性
glBindBuffer(GL_ARRAY_BUFFER, model_matrix_buffer);
// 循环遍历矩阵的每一列...
for (int i = 0; i < 4; i++) {
    // 设置顶点属性
    glVertexAttribPointer(matrix_loc + i,               // 位置
                          4, GL_FLOAT, GL_FALSE,        // vec4
                          sizeof(mat4),                 // 数据步幅
                          (void *)(sizeof(vec4) * i));  // 起始偏移值
    // 启用顶点属性
    glEnableVertexAttribArray(matrix_loc + i);
    // 实现多实例化
    glVertexAttribDivisor(matrix_loc + i, 1);
}