#version 330 core

// 来自应用程序的位置和二维纹理坐标
layout (location = 0) in vec2 in_position;
layout (location = 1) in vec2 in_tex_coord;

// 输出变换后的三维纹理坐标
out vec3 tex_coord;

// 把纹理坐标转换到三维空间的矩阵
uniform mat4 tc_rotate;

void main() {
    // 用变换矩阵乘纹理坐标把它变换进三维空间
    tex_coord = (vec4(in_tex_coord, 0.0, 1.0) * tc_rotate).stp;
    gl_Position = vec4(in_position, 0.5, 1.0);
}
