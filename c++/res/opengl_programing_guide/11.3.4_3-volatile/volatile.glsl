#version 420 core

// 声明一个图像 uniform 为 volatile。
// 编译器不会对这个图像的内容做任何的推测，也不会对这个图像相关的代码执行任何不安全的优化处理
layout (r32ui) uniform volatile uimageBuffer my_image;

// 函数的参数声明也可以使用 volatile...

void functionTakingVolatileImage(volatile uimageBuffer) {
    // 在这里读取和写入 i
}
