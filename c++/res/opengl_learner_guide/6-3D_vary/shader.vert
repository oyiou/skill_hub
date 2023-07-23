#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;				// 颜色变量的顶点属性位置值为 1
out vec3 ourColor;
uniform mat4 transform_1;						// 一个分号差点要了我的命....
void main()
{
    ourColor = color;
    gl_Position = transform_1 * vec4(position, 1.0f);
}