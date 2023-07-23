#version 330 core

// 输入为三角形，四个请求（实例）
layout (triangles, invocations = 4) in;
// 输出为三角带，每个请求有三个顶点
layout (triangle_strip, max_vertices = 3) out;

// 需要四个模型矩阵以及一个通用的投影矩阵
uniform mat4 model_matrix[4];
uniform mat4 projection_matrix;

// 来自顶点着色器的通常输入
in vec3 vs_normal[];

// 将颜色和法线输出到片元着色器
out vec4 gs_color;
out vec3 gs_normal;

// 用于四个实例中的不同颜色值
const vec4 colors[4] = vec4[4] (
    vec4(1.0, 0.7, 0.3, 1.0),
    vec4(1.0, 0.2, 0.3, 1.0),
    vec4(0.1, 0.6, 1.0, 1.0),
    vec4(0.3, 0.7, 0.5, 1.0)
);

void main() {
    for (int i = 0; i < gl_in.length(); i++) {
        // 设置每个顶点的视口索引
        gl_ViewportIndex = gl_InvocationID;
        // 从 colors 数组中读取颜色值，索引为 gl_InvocationID
        gs_color = colors[gl_InvocationID];
        // 通过模型矩阵变换得到法线值。注意，这里假设模型，矩阵中不存在剪切
        gs_normal = (model_matrix[gl_InvocationID] * vec4(vs_normal[i], 0.0)).xyz;
        // 最后，将顶点变换到位置变量中并发射
        gl_Position = projection_matrix * (model_matrix[gl_InvocationID] * gl_in[i].gl_Position);
        EmitVertex();
    }
}
