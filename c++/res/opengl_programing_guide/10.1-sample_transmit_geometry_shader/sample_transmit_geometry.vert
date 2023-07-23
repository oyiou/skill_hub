// 这是一个非常简单的传递几何着色器
#version 330 core

// 设置输入和输出的图元类型，以及着色器中产生的最大顶点数量。
// 这里设置输入类型为三角形，而输出为三角形条带
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

// 几何着色器和其他类型的着色器一样，都必须有一个 main 函数
void main() {
    int n;

    // 遍历所有输入的顶点
    for (n = 0; n < gl_in.length(); n++) {
        // 将输入位置拷贝到输出位置上
        gl_Position = gl_in[0].gl_Position;
        // 发射顶点数据
        EmitVertex();
    }
    // 完成图元。在这里这一步并不是必需的，只是用作演示的目的
    EndPrimitive();
}
