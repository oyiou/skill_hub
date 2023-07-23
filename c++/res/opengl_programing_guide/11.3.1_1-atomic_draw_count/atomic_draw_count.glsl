#version 420 core

// 使用图像变量来保存场景绘制计数的结果
layout (r32ui) uniform uimage2D overdraw_count;

void main(void) {
    // 采取原子操作对内存中的数值加一
    imageAtomicAdd(overdraw_count, ivec2(gl_FragCoord.xy), 1);
}
