//
// Created by leever on 2023/3/30.
//
#include "opengl_programing_guide.h"

// 观察矩阵和投影矩阵在绘制过程中都是常数
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

// 顶点着色器的输出（对应于片元着色器的输入）
out VERTEX {
    vec3 normal;
    vec4 color;
} vertex;

void main(void) {
    // 根据 uniform 的观察矩阵和逐实例的米星矩阵构建完整的模型——视点矩阵
    mat4 model_view_matrix = view_matrix * model_matrix;

    // 首先用模型——视点矩阵变换位置，然后是投影矩阵
    gl_Position = projection_matrix * (model_view_matrix * position);

    // 使用模型——视点矩阵的左上 3x3 子子矩阵变换法线
    vertex.normal = mat3(model_view_matrix) * normal;

    // 将逐实例的颜色值直接传入片元着色器
    vertex.color = color;
}