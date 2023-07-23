#version 330 core

uniform mat4 ModelViewProject;
in vec4 Vertex;

void main() {
    gl_Position = ModelViewProject * Vertex;
}
