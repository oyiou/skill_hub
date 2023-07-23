//
// Created by leever on 2023/5/9.
//
#include "opengl_programing_guide.h"

// 声明变量
GLuint tex; // 这就是二维数组纹理
GLuint fbo; // 这是帧缓存对象

// 创建并分配一个 1024x1024x32 的二维数组纹理
glGenTextures(1, &tex);
glBindTexture(GL_TEXTURE_2D_ARRAY, tex);
glTexImage3D(GL_TEXTURE_2D_ARRAY,
             0,
             GL_RGBA,
             1024,
             1024,
             32,
             0,
             GL_RGBA,
             GL_UNSIGNED_BYTE,
             NULL);
// 创建一个帧缓存对象，将二维数组纹理关联到它的颜色附件上
glGenFramebuffers(1, &fbo);
glBindFramebuffer(GL_FRAMEBUFFER, fbo);
glFramebufferTexture(GL_FRAMEBUFFER,
                     GL_COLOR_ATTACHMENT0,
                     tex,
                     0);
// 现在将帧缓存的颜色，附件作为当前的绘制缓存
static const GLenum draw_buffers[] = {
        GL_COLOR_ATTACHMENT0
};
glDrawBuffers(1, draw_buffers);