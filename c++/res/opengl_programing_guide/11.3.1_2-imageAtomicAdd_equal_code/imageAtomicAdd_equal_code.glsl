// 这个函数的执行必需是原子式的
uint imageAtomicAdd(uimage2D image, ivec2 P, uint data) {
    // 读取当前内存中的数值
    uint val = imageLoad(image, P).x;
    // 将新的值写入内存中
    imageStore(image, P, uvec4(val + data));
    // 返回 旧 的值
    return val;
}