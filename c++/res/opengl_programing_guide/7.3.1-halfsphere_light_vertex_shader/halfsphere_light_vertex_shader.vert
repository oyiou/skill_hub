#version 330 core

uniform vec3 LightPosition;
uniform vec3 SkyColor;
uniform vec3 GroundColor;

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;

in vec4 VertexPosition;
in vec3 VertexNormal;

out vec3 Color;

void main() {
    vec3 position = vec3(MVMatrix * VertexPosition);
    vec3 tnorm = normalize(LightPosition * VertexNormal);
    vec3 lightVec = normalize(LightPosition - position);
    float costheta = dot(thorm, lightVec);
    float a = costheta * 0.5 + 0.5;
    Color = mix(GroundColor, SkyColor, a);
    gl_Position = MVPMatrix * VertexPosition;
}
