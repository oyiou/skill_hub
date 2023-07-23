// 无光照的片元着色器
#version 330 core

in vec4 Color;  // 在顶点之间插值

out vec4 FragColor; // 片元的颜色结果

void main() {
    FragColor = Color;
}
