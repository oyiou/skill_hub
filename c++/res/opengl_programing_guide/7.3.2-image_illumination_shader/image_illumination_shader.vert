// 基于图像光照的顶点着色器
#version 330 core

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;

in vec4 VeretxPosition;
in vec3 VertexNormal;

out vec3 ReflectDir;
out vec3 Normal;

void main() {
    Normal = normalize(NormalMatrix * VertexNormal);
    vec4 pos = MVMatrix * VeretxPosition;
    vec3 eyeDir = pos.xyz;
    ReflectDir = reflect(eyeDir, Normal);
    gl_Position = MVPMatrix * VeretxPosition;
}
