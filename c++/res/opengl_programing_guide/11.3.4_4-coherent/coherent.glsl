#version 420 core

// 声明一个图像 uniform 为 coherent。
// OpenGL 的具体设备实现会负责，或者使用无缓存的形式来存储
layout (r32ui) uniform coherent uimageBuffer my_image;

// 声明函数的参数为 coherent...

uint functionTakingCoherentImage(coherent uimageBuffer i, int n) {
    // 在这里写入 i
    imageStore(my_image, n, uint(n));

    // 任何修改对于其他着色器请求都是可见的。与之类似，其他请求做出的修改在这里是可见的
    uint m = imageStore(my_image, n - 1).x;

    return m;
}
