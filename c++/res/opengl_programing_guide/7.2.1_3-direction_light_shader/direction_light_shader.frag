// 计算方向光的光照结果所用的片元着色器
#version 330 core

uniform vec3 Ambient;
uniform vec3 LightColor;
uniform vec3 LightDirection;    // 光照的方向
uniform vec3 HelfVector;    // 光泽度的表面方向
uniform float Shininess;    // 高度尖锐程度的指数值
uniform float Strength; // 用于调整光泽度的数据

in vec4 Color;
in vec3 Normal; // 顶点之间插值得到的法线数据

out vec4 FragColor;

void main() {
    // 计算方向的余弦值，使用点积的方法来判断光照的反射程度
    float diffuse = max(0.0, dot(Normal, LightDirection));
    float specular = max(0.0, dot(Normal, HelfVector));

    // 远离光照方向的表面（负数的点积结果）不会被方向光照亮
    if (diffuse == 0.0)
        specular = 0.0;
    else
        specular = pow(specular, Shininess);    // 高光效果

    vec3 scatteredLight = Ambient + LightColor * diffuse;
    vec3 reflectedLight = LightColor * specular * Strength;
    // 不要将表面颜色与反射光进行调制，只需要和漫反射结果叠加即可

    vec3 rgb = min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
    FragColor = vec4(rgb, Color.a);
}
