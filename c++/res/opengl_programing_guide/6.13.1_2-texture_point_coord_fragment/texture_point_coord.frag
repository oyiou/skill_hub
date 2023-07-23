#version 330 core

uniform sampler2D sprite_texture;

out vec4 color;

void main() {
    color = texture(sprite_texture, gl_PointCoord);
}
