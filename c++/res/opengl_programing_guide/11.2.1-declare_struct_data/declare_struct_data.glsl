#version 430 core

// 一个数据对象的结构体
struct ItemType {
    int count;
    vec4 data[3];
    // ...其他域成员
};

// 声明一个使用 ItemType 的缓存块
layout (std430, binding = 0) buffer BufferObject {
    // ...定义其他的数据
    ItemType items[];   // 最后定义大小未定的数组（在运行时再声明）
};