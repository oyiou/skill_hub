#version 330 core
// in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture_1;		// 负责纹理一的采样器
uniform sampler2D ourTexture_2;		// 负责纹理二的采样器
uniform float time;
void main()
{
    FragColor = mix(texture(ourTexture_1, TexCoord), texture(ourTexture_2, TexCoord), time); // 混合重叠
}