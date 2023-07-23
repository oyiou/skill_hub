//
// Created by leever on 2023/5/9.
//
GLuint tex;

// 为纹理生成一个新的名称
glGenTextures(1, &tex);
// 绑定到规则的 2D 纹理目标，即创建纹理
glBindTexture(GL_TEXTURE_2D, tex);
// 为纹理分配不可变的存储空间
glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, 512, 512);
// 解除 2D 纹理目标的绑定
glBindTexture(GL_TEXTURE_2D, 0);
// 现在将它绑定到一个图像单元上，并且设置为可读可写状态
glBindImageTexture(0, tex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);