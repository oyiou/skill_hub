#version 420 core

layout (rgba32f) uniform coherent image2D my_image;

// 声明函数
void functionUsingBarriers(coherent uimageBuffer i) {
    uint val;

    // 这个循环本质上只是等待至少一个来自之前的图元（序号为 gl_PrimitiveID - 1）的片元到达函数尾部。
    // 注意这并不是一个稳定的循环结构，因为并不是所有的图元都会产生片元
    do {
        val = imageLoad(i, 0).x;
    } while(val != gl_PrimitiveID);

    // 在这里，从另外一个全局的图像加载数据
    vec4 frag = imageLoad(my_image, gl_FragCoord,xy);

    // 对它进行操作...
    frag *= 0.1234;
    frag = pow(frag, 2.2);

    // 将数据写回到内存中
    imageStore(my_image, gl_FragCoord.xy, frag);

    // 现在需要发出通知，说明已经完成片元的处理。
    // 要确保所有的存储操作都已经在内存中完成，因此在这里插入一个内存屏障（memory barrier）
    memoryBarrier();

    // 现在要写回到“图元计数器”内存中，以标识所在的位置。
    // 不过 my_image 处理的结果会先一步到达内存中，然后才是这里的存储操作，这就算屏障的作用
    imageStore(i, 0, gl_PrimitiveID + 1);

    // 还要再加入另一个屏障，确保图像存储的结果先进入内存，然后再结束当前的着色器请求操作
    memoryBarrier();
}