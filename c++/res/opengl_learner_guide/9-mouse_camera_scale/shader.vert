#version 330 core
layout (location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

out vec3 ourColor;
out vec3 FragNormal;
out vec3 FragPos;

uniform mat4 transform_1;
uniform mat4 projection_1;
uniform mat4 view_1;

void main()
{
    ourColor = color;
    gl_Position = projection_1 * view_1 * transform_1 * vec4(position, 1.0f);
    FragPos = vec3(transform_1 * vec4(position, 1.0f));
    FragNormal = normal;
}