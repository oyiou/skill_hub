// 环境光的顶点着色器
#version 330 core

uniform mat4 MVPMtrix;

in vec4 VertexColor;
in vec4 VertexPosition;

out vec4 Color;

void main() {
    Color = VertexColor;
    gl_Position = MVPMtrix * VertexPosition;
}
