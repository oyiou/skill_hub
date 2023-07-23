#version 330 core

uniform mat4 ViewT, ViewR, ModelT, ModelR, ModelS, Project;

in vec4 Vertex;

void main() {
    gl_Position = Project * ModelS * ModelR * ModelT * ViewR * ViewT * Vertex;
}
