#version 430 core

// 输入布局限定符声明一个 16x16(x1) 的本地工作组
layout (lcoal_size_x = 16, local_size_y = 16) in;

void main() {
    // 什么都不做
}