//
// Created by leever on 2023/4/4.
//
#include "opengl_programing_guide.h"

void init(void) {
    // ... // 设置顶点数组等信息
    // 设置模板的清除值
    glClearStencil(0x0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
}
// 在菱形区域内绘制一个球体，它正好位于两个圆环的窗口中心
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 模板值为 1 的时候绘制球体
    glStencilFunc(GL_EQUAL, 0x1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    drawSphere();

    // 模板值不是 1 的时候绘制圆环
    glStencilFunc(GL_NOTEQUAL, 0x1, 0x1);
    drawTori();
}
// 窗口发生变形之后，重新定义坐标并且重绘制模板区域
void reshape(int width, int height) {
    glViewport(0, 0, width, height);

    // 创建一个菱形的模板区域
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS, 0x1, 0x1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    drawMask();
}