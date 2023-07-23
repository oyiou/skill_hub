// 点光源（局部）光照计算的片元着色器
#version 330 core

uniform vec3 Ambient;
uniform vec3 LightColor;
uniform vec3 LightPosition; // 人眼坐标下光源的位置
uniform float Shininess;
uniform float Strength;

uniform vec3 EyeDirection;
uniform float ConstantAttenuation;  // 衰减系数
uniform float LinearAttenuation;
uniform float QuadraticAttenuation;

in vec4 Color;
in vec3 Normal;
in vec4 Position;

out vec4 FragColor;

void main() {
    // 获取光照的方向和距离，它们会逐个片元地发生改变
    vec3 lightDirection = LightPosition - vec3(Position);
    float lightDistance = length(lightDirection);

    // 对光照方向向量进行归一化，这样点积的结果就算余弦值
    lightDirection = lightDirection / lightDistance;

    // 判断当前片元接收的光照程度
    float attenuation = 1.0 / (ConstantAttenuation + LinearAttenuation * lightDistance + QuadraticAttenuation * lightDistance * lightDistance);

    // 每个片元的最大高光方向也是不断变化的
    vec3 helfVector = normalize(lightDirection + EyeDirection);

    float diffuser = max(0.0, dot(Normal, lightDirection));
    float specular = max(0.0, dot(Normal, helfVector));

    if (diffuser == 0.0)
        specular = 0.0;
    else
        specular = pow(specular, Shininess) * Strength;

    vec3 scatteredLight = Ambient + LightColor * diffuser * attenuation;
    vec3 reflectedLight = LightColor * specular * attenuation;
    vec3 rgb = min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
    FragColor = vec4(rgb, Color.a);
}
