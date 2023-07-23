#version 330 core
layout (location = 0) in vec3 position;			// 坐标变量的顶点属性位置值为 1
layout(location = 1) in vec3 color;				// 颜色变量的顶点属性位置值为 1
layout(location = 2) in vec2 textureCoords;		// 纹理坐标只有两个浮点数 (s,t), 属性位置值为 2
out vec2 TexCoord;
// out vec3 ourColor;
uniform mat4 transform_1;						// 一个分号忘了加, 差点要了我的命....
void main()
{
    // ourColor = color;
    gl_Position = transform_1 * vec4(position, 1.0);	// transform_1 就是那个变换矩阵
    TexCoord = vec2(textureCoords.x, 1-textureCoords.y);
}