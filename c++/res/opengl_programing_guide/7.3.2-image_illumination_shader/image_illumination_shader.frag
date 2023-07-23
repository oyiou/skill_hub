// 基于图像光照的片元着色器
#version 330 core

uniform vec3 BaseColor;
uniform float SpecularPercent;
uniform float DiffusePercent;
uniform samplerCube SpecularEnvMap;
uniform samplerCube DiffuseEnvMap;

in vec3 ReflectDir;
in vec3 Normal;

out vec4 FragColor;

void main() {
    // 从 cubemap 贴图中查找环境贴图值
    vec3 diffuseColor = vec3(texture(DiffuseEnvMap, normalize(Normal)));
    vec3 specularColor = vec3(texture(SpecularEnvMap, normalize(ReflectDir)));

    // 将光照结果添加到基础颜色中进行混合
    vec3 color = mix(BaseColor, diffuseColor * BaseColor, DiffusePercent);
    color = mix(color, specularColor + color, SpecularPercent);
    FragColor = vec4(color, 1.0);
}
