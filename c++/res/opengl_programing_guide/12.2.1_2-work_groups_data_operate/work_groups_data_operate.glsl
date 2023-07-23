#version 430 core

layout (local_size_x = 32, local_size_y = 16) in;

// 存储数据的图像变量
layout (rg32f) uniform image2D data;

void main(void) {
    // 将本地请求 ID 存储到图像中
    imageStore(data,
                ivec2(gl_GlobalInvocationID,xy),
    vec4(vec2(gl_LocalInvocationID.xy) / vec2(gl_WorkGroupSize.xy),
        0.0, 0.0));
}
