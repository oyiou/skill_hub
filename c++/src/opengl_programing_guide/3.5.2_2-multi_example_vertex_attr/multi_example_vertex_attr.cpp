//
// Created by leever on 2023/3/31.
//
#include "opengl_programing_guide.h"

// 获取顶点属性在 prog 当中的位置，prog 就是准备用于渲染的着色器程序对象
// 注意，这一步并不是必需的，因为已经在顶点着色器中设置了所有属性的位置。这里的代码可以编写更简单一些，只需要直接给出程序中已经设置的属性位置即可
int position_loc = gl3wGetAttribLocation(prog, "position");
int normal_loc = gl3wGetAttribLocation(prog, "normal");

// 配置正规的顶点属性数组——顶点和法线
glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
glVertexAttribPointer(position_loc, 4, GL_FLOAT, GL_FALSE, 0, NULL);
glEnableVertexAttribArray(position_loc);
glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
glEnableVertexAttribArray(normal_loc);

// 现在设置多实例颜色和模型矩阵的 TBO
// 首先创建 TBO 来存储颜色值，绑定一个缓存然后初始化数据格式。
// 缓存必须在之前已经创建，并且大小可以包含一个 vec4 的逐实例数据
glGenTextures(1, &color_tbo);
glBindTexture(GL_TEXTURE_BUFFER, color_tbo);
glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, color_buffer);
// 再次使用 TBO 来存储模型矩阵值。这个缓存对象（model_matrix_buffer）必须在之前已经创建，并且大小可以包含一个 mat4 的逐实例数据
glGenTextures(1, &model_matrix_tbo);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_BUFFER, model_matrix_tbo);
glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, model_matrix_buffer);