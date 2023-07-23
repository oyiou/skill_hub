#version 420 core

uniform uimageBuffer counter_buffer;
uniform sampler2D my_texture;

in vec2 tex_coord;

layout (location = 0) out vec4 fragment_color;

void main(void) {
    vec4 texel_color = texture(my_texture, tex_coord);

    if (texel_color.r > texel_color.g) {
        imageAtomicAdd(counter_buffer, 0, 1);
    } else {
        imageAtomicAdd(counter_buffer, 1, 1);
    }

    FragColor = texel_color;
}
