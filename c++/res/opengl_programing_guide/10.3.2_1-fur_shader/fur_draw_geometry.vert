// 毛发渲染的几何着色器
#version 330 core

// 输入和输出均为三角形，设置一个较大的 max_vertices 值以实现扩充的需求
layout (triangles) in;
layout (triangle_strip, max_vertices = 120) out;

uniform mat4 model_matrix;
uniform mat4 projection_matrix;

// 来自顶点着色器的输入
in VS_GS_VERTEX {
    vec3 normal;
    vec2 tex_coord;
} vertex_in[];

// 向片元着色器输出的内容
out GS_FS_VERTEX {
    vec3 normal;
    vec2 tex_coord;
    flat float fur_strength;
} vertex_out;

void main() {
    int i, layer;
    // 在各层之间进行置换的值
    float disp_delta = 1.0 / float(fur_layers);
    float d = 0.0;

    // 对于每一层...
    for (layer = 0; layer < fur_layers; layer++) {
        // 对每个输入的顶点（数量应该都是 3）
        for (i = 0; i < gl_in.length(); i++) {
            // 获取顶点法线
            vec3 n = vertex_in[i].normal;
            // 将它拷贝到输出变量，传递给片元着色器
            vertex_out.normal = n;
            // 拷贝纹理坐标——需要用它来获取毛发纹理
            vertex_out.tex_coord = vertex_in[i].tex_coord;
            // 沿着毛发的长度线性地减少毛发的“强度”
            vertex_out.fur_strength = 1.0 - d;
            // 这是关键所在——对每个顶点沿着法线进行置换，生成 fur shell
            position = gl_in[i].gl_Position + vec4(n * d * fur_depth, 0.0);
            // 变换到适当的位置，发射顶点
            gl_Position = projection_matrix * (model_matrix * position);
            EmitVertex();
        }
        // 使用计算得到的间隔值继续向外移动
        d += disp_delta;
        // 结束当前图元条带，准备进入下一层
        EndPrimitive();
    }
    gl_Position = vec4(vec3(0.0), 1.0);
}
