#version 430 core

// 创建一个可读可写的缓存
layout (std430, binding = 0) buffer BufferObject {
    int mode;   // 序号
    vec4 points;    // 最后一个成员可以是一个未定义大小的数组
};