#version 420 core

// 准备在循环中读取的图像变量
layout (r32ui) uniform uimageBuffer my_image;

void waitForImageToBeNonZero() {
    uint val;

    // 着色器编译器认为图像数据是不会发生变化的，因此直接将它移动到循环之外
    val = imageLoad(my_image, 0).x;

    do {
        // 循环中没有别的东西了，那么它要么第一次迭代后就退出，要么一直运行下去
    } while(val == 0);
}
