// 从片元着色器中抽取点光源计算的结果到顶点着色器中
#version 330 core

uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;

uniform vec3 LightPosition; // 现在传入顶点着色器中
uniform vec3 EyeDirection;
uniform float ConstantAttenuation;
uniform float LinearAttenuation;
uniform float QuadraticAttenuation;

in vec4 VertexColor;
in vec3 VertexNormal;
in vec4 VertexPosition;

out vec4 Color;
out vec3 Normal;
// out vec4 Position;   // 不再需要这个值了

out vec3 LightDirection;    // 直接发送结果
out vec3 HelfVector;
out float Attenuation;

void main() {
    Color = VertexColor;
    Normal = normalize(NormalMatrix * VertexNormal);

    // 在顶点着色器而不是片元着色器中进行计算

    LightDirection = LightPosition - vec3(VertexPosition);
    float lightDistance = length(LightDirection);

    LightDirection = LightDirection / lightDistance;

    Attenuation = 1.0 / (ConstantAttenuation + LinearAttenuation * lightDistance + QuadraticAttenuation * lightDistance * lightDistance);

    HelfVector = normalize(LightDirection + EyeDirection);

    gl_Position = MVPMatrix * VertexPosition;
}
