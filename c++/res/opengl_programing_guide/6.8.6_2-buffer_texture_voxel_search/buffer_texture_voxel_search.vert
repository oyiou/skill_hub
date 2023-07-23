#version 330 core

uniform samplerBuffer buf;
in int buf_tex_coord;

layout (location = 0) out vec4 color;

void main(void) {
    color = texelFetch(buf, tex_coord);
}
