#version 420 core

layout (r32ui) uniform uimage2D lock_image;
layout (rgba8f) uniform image2D protected_image;
void takeLock(ivec2 pos) {
    int lock_available;

    do {
        // 锁的设置——如果锁没有设置，那么 lock_image 的值为 0。
        // 这样的话，函数返回的是内存中原先的值——如果没有设置为 0，否则为 1。
        // 如果锁没有设置，那么将结束当前循环，并且同时已经向内存中写入 1。
        lock_available = imageAtomicCompSwap(lock_image, pos, 0, 1);
    } while (lock_available == 0);
}

void releaseLock(ivec2 pos) {
    imageStore(lock_image, pos, 0);
}

void operateOnFragment() {
    // 如果当前片元是不可分的，那么在这里执行一系列操作。
    // 这里简单地进乘以一个常量，并且没有用到原子函数（例如 imageAtomicMult）。
    // 当然现在可以很轻松地实现一些更复杂的函数内容。
    vec4 old_fragment;

    old_fragment = imageLoad(protected_image, ivec2(gl_FragCoord.xy));

    imageStore(protected_image, ivec2(gl_FragCoord.xy), old_fragment * 13.37);
}

void main(void) {
    // 设置一个逐像素的锁
    takeLock(ivec2(gl_FragCoord.xy));

    // 现在已经有了锁，可以安全地操作共享的资源了
    operateOnPixel();

    // 不要忘记最后释放锁
    releaseLock(ivec2(gl_FragCoord.xy));
}