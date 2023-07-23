// 在片元着色器中计算方向光时，所有顶点着色器
#version 330 core

uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;  // 用于变换法线

in vec4 VertexColor;
in vec3 VertexNormal;   // 需要传入表面的法线
in vec4 VeretxPosition;

out vec4 Color;
out vec3 Normal;    // 对归一化之后的表面法线进行插值

void main() {
    Color = VertexColor;

    // 执行法线变换并归一化，不考虑透视的影响
    Normal = normalize(NormalMatrix * VertexNormal);

    gl_Position = MVPMatrix * VeretxPosition;
}
