#version 420 core

// 准备在循环中读取图像变量
layout (r32ui) uniform uimageBuffer my_image;

void waitForImageToBeNonZero() {
    uint val;

    do {
        // 从固定的位置回读图像数据
        val = imageLoad(my_image, 0).x;
        // 一直循环，直到返回值非零为止
    } while(val == 0);
}