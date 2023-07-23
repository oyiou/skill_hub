#version 330 core

uniform mat4 M;
in vec4 Vertex;

void main() {
    gl_Position = Vertex * M;   // 非常规的乘法顺序
}
