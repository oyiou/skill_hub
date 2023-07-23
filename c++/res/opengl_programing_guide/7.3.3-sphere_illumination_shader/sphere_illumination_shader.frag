// 计算球面光照的片元着色器
#version 330 core

in vec3 DiffuseColor;

out vec4 FragColor;

void main() {
    FragColor = vec4(DiffuseColor, 1.0);
}
