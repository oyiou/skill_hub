#version 420 core

layout (quads, epual_spacing, ccw) out;

uniform mat4 MV;    // 模型视图矩阵
uniform mat4 P; // 投影矩阵

void main() {
    vec4 p = vec4(0.0);

    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 4; ++i) {
            p += B(i, u) * B(j, v) * gl_in[4 * j+i].gl_Position;
        }
    }

    gl_Position = P * MV * p;
}
