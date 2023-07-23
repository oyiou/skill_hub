// 无光照的顶点着色器
#version 330 core

uniform mat4 MVPMatrix; // 模型视图投影矩阵

in vec4 VertexColor;    // 应用程序端发送，包含 alpha
in vec4 VertexPosition; // 变换之前的位置

out vec4 Color; // 输出到光栅化阶段进行插值

void main() {
    Color = VertexColor;
    gl_Position = MVPMatrix * VertexPosition;
}
