// 这个函数会自动执行
uvec4 imageAtomicExchange(uimage2D image, ivec2 P, uint data) {
    uvec4 val = imageLoad(image, P);
    imageStore(image, P, data);
    return val;
}

// 这个函数会自动执行
uvec4 imageAtomicCompSwap(uimage2D image, ivec2 P, uint compare, uint data) {
    uvec4 val = imageLoad(image, P);
    if (compare == val) {
        imageStore(image, P, data);
    }
    return val;
}