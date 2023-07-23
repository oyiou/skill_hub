#version 430 core

// 图像的一行扫描线...1024 是 OpenGL 可用的最大值
layout (local_size_x = 1024) in;

// 输入和输出图像
layout (rgba32f, binding = 0) uniform image2D input_image;
layout (rgba32f, binding = 1) uniform image2D output_image;

// 使用共享内存来保存扫描线数据——它的大小必须与本地工作组一样（或者更大）
shared vec4 scanline[1024];

void main(void) {
    // 获取图像的当前位置
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);

    // 读取输入像素，保存到共享数组中
    scanline[pos.x] = imageLoad(input_image, pos);

    // 确保所有其他的请求都到达这个位置，并且在调用 barrier() 之前已经完成共享数据的写入
    barrier();

    // 计算结果并写回到图像中
    vec4 result = scanline[min(pos.x + 1, 1023)] - scanline[max(pos.x - 1, 0)];
    imageStore(output_image, pos.xy, result);
}
