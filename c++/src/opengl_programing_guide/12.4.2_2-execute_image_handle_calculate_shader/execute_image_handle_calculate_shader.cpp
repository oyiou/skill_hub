//
// Created by leever on 2023/5/11.
//
#include "opengl_programing_guide.h"

// 激活计算着色器
glUseProgram(compute_prog);

// 绑定源图像为输入，中间图像为输出
glBindImageTexture(0, input_image, 0,
                   GL_FALSE, 0,
                   GL_READ_ONLY, GL_RGBA32F);
glBindImageTexture(1, intermediate_image, 0,
                   GL_FALSE, 0, GL_WRITE_ONLY,
                   GL_RGBA32F);
// 执行水平运算过程
glDispatchCompute(1, 1024, 1);
// 在两个过程之间插入一个内存屏障
glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
// 现在绑定中间图像为输入，最终图像为输出
glBindImageTexture(0, intermediate_image, 0,
                   GL_FALSE, 0,
                   GL_READ_ONLY, GL_RGBA32F);
glBindImageTexture(1, output_image, 0,
                   GL_FALSE, 0,
                   GL_WRITE_ONLY, GL_RGBA32F);
// 执行垂直运算过程
glDispatchCompute(1, 1024, 1);