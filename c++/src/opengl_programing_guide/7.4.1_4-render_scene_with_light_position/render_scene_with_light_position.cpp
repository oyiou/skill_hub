//
// Created by leever on 2023/5/4.
//
#include "opengl_programing_guide.h"

// 绑定深度 FBO 并且设置视口为深度纹理的大小
glBindFramebuffer(GL_FRAMEBUFFER, depth_fbo);
glViewport(0, 0, DEPTH_TEXTURE_SIZE, DEPTH_TEXTURE_SIZE);

// 清除缓存
glClearDepth(1.0f);
glClear(GL_DEPTH_BUFFER_BIT);

// 打开多边形偏移，以避免深度数据的 z-fighting 问题
glEnable(GL_POLYGON_OFFSET_FILL);
glPolygonOffset(2.0f, 4.0f);

// 从光源位置进行绘制
DrawScene(true);
glDisable(GL_POLYGON_OFFSET_FILL);