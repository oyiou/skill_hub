// 顶点着色器
#version 430 core

layout(location = 0) ivec4 vPosition;

void main() {
    gl_Position = vPosition;
}
