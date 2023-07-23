// 全局环境光的片元着色器
#version 330 core

uniform vec4 Ambient;   // 设置光照的等级，对于很多顶点都是相同的

in vec4 Color;

out vec4 FragColor;

void main() {
    vec4 scatteredLight = Ambient;  // 唯一的光源
    // 将表面颜色与光照颜色进行调制，但是最大值是全白色
    FragColor = min(Color * scatteredLight, vec4(1.0));
}
