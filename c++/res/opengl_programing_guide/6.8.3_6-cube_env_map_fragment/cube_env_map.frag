#version 330 core

// 传入的表面法线和观察空间位置
in vec3 vs_fs_normal;
in vec3 vs_fs_position;

// 最终的片元颜色
layout (location = 0) out vec4 color;

// 立方体映射纹理
uniform samplerCube tex;

void main() {
    // 通过沿表面法线反射观察空间位置来计算纹理坐标
    vec3 tc = reflect(-vs_fs_position, normalize(vs_fs_normal));
    // 采样纹理，结果像素着色为金色
    color = vec4(0.3, 0.2, 0.1, 1.0) + vec4(0.97, 0.83, 0.79, 0.0) * texture(tex, tc);
}
