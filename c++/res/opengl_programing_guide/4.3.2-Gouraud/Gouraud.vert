#version 330 core

layout(location = 0) in vec4 vPostion;
layout(location = 1) in vec4 vColor;

out vec4 color;

void main() {
    color = vColor;
    gl_Position = vPostion;
}