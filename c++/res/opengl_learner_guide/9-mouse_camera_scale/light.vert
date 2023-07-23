#version 330 core
layout (location = 0) in vec3 position;
uniform mat4 transform_2;
uniform mat4 projection_2;
uniform mat4 view_2;
void main()
{
    gl_Position = projection_2 * view_2 * transform_2 * vec4(position, 1.0f);
}