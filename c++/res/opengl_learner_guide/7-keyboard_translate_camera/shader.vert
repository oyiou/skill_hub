#version 330 core
layout (location = 0) in vec3 position;
layout(location = 1) in vec3 color;				// 颜色变量的顶点属性位置值为 1
out vec3 ourColor;
uniform mat4 transform_1;
uniform mat4 projection_1;
uniform mat4 view_1;
void main()
{
    ourColor = color;
    gl_Position = projection_1 * view_1 * transform_1 * vec4(position, 1.0f);	 // 注意矩阵乘法要从右向左读
}