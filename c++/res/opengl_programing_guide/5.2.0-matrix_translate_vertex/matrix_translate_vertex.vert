#version 330 core

uniform mat4 Transform;  // 对于各个顶点都是一致的（图元级别的粒度）

in vec4 Vertex; // 每次传递的逐顶点数据

void main() {
    gl_Position = Transform * Vertex;
}
