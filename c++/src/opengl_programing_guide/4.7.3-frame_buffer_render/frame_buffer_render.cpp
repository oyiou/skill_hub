//
// Created by leever on 2023/4/7.
//
#include "opengl_programing_guide.h"

enum {Color, Depth, NumRenderbuffers};

GLuint framebuffer, renderbuffer[NumRenderbuffers];

void init() {
    glGenRenderbuffers(NumRenderbuffers, renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer[Color]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, 256, 256);

    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer[Depth]);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 256, 256);

    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer[Color]);

    glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer[Depth]);

    glEnable(GL_DEPTH_TEST);
}

void display() {
    // 准备渲染到渲染缓存当中
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

    glViewport(0, 0, 256, 256);

    // 渲染到渲染缓存
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ...

    // 设置从渲染缓存读取，然后绘制窗口系统的帧缓存中
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glViewport(0, 0, windowsWidth, windowHEight);
    glClear(0.0, 0.0, 1.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 执行拷贝操作
    glBlitFramebuffer(0, 0, 255, 255, 0, 0, 255, 255, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glutSwapBuffers();
}