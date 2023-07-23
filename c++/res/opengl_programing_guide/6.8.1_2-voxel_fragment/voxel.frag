#version 330 core

// 来自顶点着色器的纹理坐标
in vec3 tex_coord;

// 最终结果
layout (location = 0) out vec4 color;

// 体纹理
uniform sampler3D tex;

void main() {
    // 简单地根据 3D 纹理坐标读取数据，然后重复使用一个通道来设置 R、G、B、A 值
    color = texture(tex, tex_coord).rrrr;
}
