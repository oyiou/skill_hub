// 点光源的计算在顶点着色器中完成，此时是片元着色器
#version 330 core

uniform vec3 Ambient;
uniform vec3 LightColor;
// uniform vec3 LightPosition;  // 不再需要
uniform float Shininess;
uniform float Strength;

in vec4 Color;
in vec3 Normal;
// in vec4 Position;    // 不再需要

in vec3 LightDirection; // 从顶点着色器中获取
in vec3 HelfVector;
in float Attenuation;

out vec4 FragColor;

void main() {
    // LightDirection、HelfVector 和 Attenuation 现在都是从顶点着色器中插值得到的

    float diffuse = max(0.0, dot(Normal, LightDirection));
    float specular = max(0.0, dot(Normal, HelfVector));

    if (diffuse == 0.0)
        specular = 0.0;
    else
        specular = pow(specular, Shininess) * Strength;

    vec3 scatteredLight = Ambient + LightColor * diffuse * Attenuation;
    vec3 reflectedLight = LightColor * specular * Attenuation;
    vec3 rgb =  min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
    FragColor = vec4(rgb, Color.a);
}
