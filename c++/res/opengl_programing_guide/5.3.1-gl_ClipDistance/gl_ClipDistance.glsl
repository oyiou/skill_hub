#version 330 core

uniform vec4 Plane; // 平面方程 Ax+By+Cz+D=0 的四个系数
in vec4 Vertex; // w == 1.0

float gl_ClipDistance[1];   // 使用一个剪切平面

void main() {
    // 计算平面方程
    gl_ClipDistance[0] = dot(Vertex, Plane);
}
