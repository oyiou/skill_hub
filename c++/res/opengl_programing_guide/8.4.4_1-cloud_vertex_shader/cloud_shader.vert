#version 330 core

uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;
uniform vec3 LightPos;
uniform float Scale;

in vec4 MCVertex;
in vec3 MCNormal;

out float LightIntensity;
out vec3 MCposition;

void main() {
    vec3 ECposition = vec3(MVMatrix * MCVertex);
    MCposition = vec3(MCVertex) * Scale;
    vec3 tnorm = normalize(vec3(NormalMatrix * MCNormal));
    LightIntensity = dot(normalize(LightPos - ECposition), tnorm);
    LightIntensity *= 1.5;
    gl_Position = MVPMatrix * MCVertex;
}
