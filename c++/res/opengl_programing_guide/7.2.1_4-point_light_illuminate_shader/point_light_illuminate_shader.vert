// 点光源（局部）的顶点着色器，计算部分是在片元着色器中完成的
#version 330 core

uniform mat4 MVPMatrix;
uniform mat4 MVMatrix;  // 需要得到透视之前的变换矩阵
uniform mat4 NormalMatrix;

in vec4 VertexColor;
in vec4 VertexNormal;
in vec4 VertexPosition;

out vec4 Color;
out vec4 Normal;
out vec4 Position;  // 位置值输出，这样才知道自己的所在

void main() {
    Color = VertexColor;
    Normal = normalize(NormalMatrix * VertexNormal);
    Position = MVMatrix * VertexPosition;   // 透视前的空间
    gl_Position = MVPMatrix * VertexPosition; // 透视后的空间
}
