// 阴影图生成的顶点着色器
#version 330 core

uniform mat4 MVPMatrix;
layout (location = 0) in vec4 position;

void main() {
    gl_Position = MVPMatrix * position;
}
