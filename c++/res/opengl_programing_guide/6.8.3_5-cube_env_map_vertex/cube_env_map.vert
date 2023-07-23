#version 330 core

// 传入的位置和法线
layout (location = 0) in vec4 in_position;
layout (location = 1) in vec3 in_normal;

// 传入的表面法线和观察空间位置
out vec3 vs_fs_normal;
out vec3 vs_fs_position;

// 模型视投影矩阵和模型视矩阵
uniform mat4 mat_mvp;
uniform mat4 mat_mv;

void main() {
    // 裁减空间位置
    gl_Position = mat_mvp * in_position;
    // 观察空概念法线和位置
    vs_fs_normal = mat3(mat_mv) * in_normal;
    vs_fs_position = (mat_mv * in_position).xyz;
}
