#version 330 core

uniform mat4 View, Project;

in vec4 Vertex;
in mat4 Model;  // 逐顶点的变换矩阵

void main() {
    gl_Position = View * Model * Project * Vertex;
}
