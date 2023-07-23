#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

void main() {
    int n;

    // 判断图元 ID 的低位，如果为真，则发射一个图元
    if ((gl_PrimitiveIDIn & 1) != 0) {
        for (n = 0; n < gl_in.length(); ++n) {
            gl_Position = gl_in[n].gl_Position;
            EmitVertex();
        }
        EndPrimitive();
    }
}
