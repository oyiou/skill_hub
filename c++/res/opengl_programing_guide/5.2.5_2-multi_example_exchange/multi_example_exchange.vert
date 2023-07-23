#version 330 core

uniform mat4 View, Model, Project;
in vec4 Vertex;

void main() {
    gl_Position = Vertex * Model * Project * Vertex;
}
