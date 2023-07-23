#version 330 core

// 输入为三角形
// 输出为点（对每个输入三角形都绘制三个点）
layout (triangles) in;
layout (points, max_vertices = 3) out;

uniform mat4 projection_matrix;

in vec3 vs_normal[];

// 数据流 0：朝向左侧的多边形
layout (stream = 0) out vec4 lf_position;
layout (stream = 0) out vec3 lf_normal;

// 数据流 1：朝向右侧的多边形
layout (stream = 1) out vec4 rf_position;
layout (stream = 1) out vec3 rf_normal;

void main() {
    // 得到三个点并获取没有归一化的面法线
    vec4 A = gl_in[0].gl_Position;
    vec4 B = gl_in[1].gl_Position;
    vec4 C = gl_in[2].gl_Position;
    vec3 AB = (B - A).xyz;
    vec3 AC = (C - A).xyz;
    vec3 face_normal = cross(AB, AC);
    int i;

    // 如果法线的 x 坐标是负数，那么它朝向观察者的左侧，也就是“朝向左侧”，因此需要将它发射到数据流 0 当中
    if (face_normal.x < 0.0) {
        // 对于每个输入顶点...
        for (i = 0; i < gl_in.length(); i++) {
            // 变换到剪切空间
            lf_position = projection_matrix * (gl_in[i].gl_Position - vec4(30.0, 0.0, 0.0, 0.0));
            // 将输入的法线拷贝到输出流
            lf_normal = vs_normal[i];
            // 发射顶点
            EmitStreamVertex(0);
        }
        // EndStreamPrimitive 的调用不是必须的，因为这些数据的类型是 points
        EndStreamPrimitive(0);
    } else {    // 否则，法线就是“朝向右侧”的，需要将它发射到数据流 1 当中
        // 与上面的意义相同，不过这次需要将 rf_position 和 rf_normal 写出到数据流 1
        for (i = 0; i < gl_in.length(); i++) {
            rf_position = projection_matrix * (gl_in[i].gl_Position - vec4(30.0, 0.0, 0.0, 0.0));
            rf_normal = vs_normal[i];
            EmitStreamVertex(1);
        }
        EndStreamPrimitive(1);
    }

}
