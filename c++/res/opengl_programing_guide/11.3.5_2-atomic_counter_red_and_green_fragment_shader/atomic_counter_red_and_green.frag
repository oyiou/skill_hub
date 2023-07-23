#version 420 core

layout (binding = 0, offset = 0) uniform atomic_uint red_texels;
layout (binding = 0, offset = 4) uniform atomic_uint green_texels;

uniform sampler2D my_texture;

in vec2 tex_coord;

layout (locatioin = 0) out vec4 fragment_color;

void main(void) {
    vec4 texel_color = texture(my_texture, tex_coord);

    if (texel_color.r > tex_coord.g) {
        atomicCounterIncrement(red_texels);
    } else {
        atomicCounterIncrement(green_texels);
    }

    fragment_color = texel_color;
}
