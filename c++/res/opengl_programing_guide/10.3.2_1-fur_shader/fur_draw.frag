// 毛发渲染的片元着色器
#version 330 core

// 一个输出值
layout (location = 0) out vec4 color;
// 毛发纹理
uniform sampler2D fur_texture;
// 毛发的颜色，默认为银灰色...
uniform vec4 fur_color = vec4(0.8, 0.8, 0.9, 1.0);

// 来自几何着色器的输入
in GS_FS_VERTEX {
    vec3 normal;
    vec2 tex_coord;
    flat float fur_strength;
} fragment_in;

void main() {
    // 获取毛发纹理值。这里只用到 alpha 通道，但是也可以使用毛发纹理的颜色值
    vec4 rgba = texture(fur_texture, fragment_in.tex_coord);
    float t = rgba.a;
    // 与几何着色器中计算的毛发强度相乘，对颜色的 alpha 值进行缩放，当前层次有 t *= fragment_in.fur_strength
    color = fur_color * vec4(1.0, 1.0, 1.0, t);
}
