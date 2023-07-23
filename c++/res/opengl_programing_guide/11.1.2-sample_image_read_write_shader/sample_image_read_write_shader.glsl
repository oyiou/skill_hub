#version 420 core

// 这个缓存包含一系列颜色值，并且通过图元的 ID 实现不同位置的读取
layout (binding = 0, rgba32f) uniform imageBuffer colors;

// 这个缓存的内容由在着色器中写入
layout (binding = 1, rgba32f) uniform image2D output_buffer;

out vec4 color;

void main(void) {
    // 根据图元 ID%256 的结果，从缓存中读取一个颜色
    vec4 col = imageLoad(colors, gl_PrimitiveID & 255);

    // 将结果片元存入两个位置。首先存入片元窗口坐标向左偏移的位置...
    imageStore(output_buffer, ivec2(gl_FragCoord.xy) - ivec2(200, 0), col);

    // ...然后存入向右偏移的位置
    imageStore(output_buffer, ivec2(gl_FragCoord.xy) + ivec2(200, 0), col);
}
