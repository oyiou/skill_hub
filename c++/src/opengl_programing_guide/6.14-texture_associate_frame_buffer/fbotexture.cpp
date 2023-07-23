//
// Created by leever on 2023/4/24.
//
#include "opengl_programing_guide.h"

GLsizei TexWidth, TexHeight;
GLuint framebuffer, texture;

void init() {
    GLuint renderbuffer;
    // 创建空纹理
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TexWidth, TexHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    // 为帧缓存创建深度缓存
    glGenRenderbuffers(1, &renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, TexWidth, TexHeight);
    // 将纹理和深度缓存关联到帧缓存
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
    glEnable(GL_DEPTH_TEST);
}

void display() {
    // 渲染到渲染缓存
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, TexWidth, TexHeight);
    glClearColor(1.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // ...
    // 生成纹理的 mipmap
    glGenerateMipmap(GL_TEXTURE_2D);
    // 绑定到 window 系统帧缓存，解除纹理的绑定
    // 这可以用作其他对象的纹理
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.0, 0.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 使用纹理 渲染
    glEnable(GL_TEXTURE_2D);
    // ...
    glutSwapBuffers();
}