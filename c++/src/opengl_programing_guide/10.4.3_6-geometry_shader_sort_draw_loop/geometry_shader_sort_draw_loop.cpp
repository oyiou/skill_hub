//
// Created by leever on 2023/5/9.
//
#include "opengl_programing_guide.h"

// 第一个过程——使用“排序”的程序对象
glUseProgram(sort_prog);

// 设置投影和模型视图矩阵
mat4 p(Frustum(-1.0f, 1.0f, aspect, -aspect, 1.0f, 5000.0f));
mat4 m;

m = mat4(translation(0.0f,
                     0.0f,
                     100.0f * sinf(6.28318531f * t) - 230.0f) *
                             rotation(360.0f * t, x) *
                             rotation(360.0f * t * 2.0f, Y) *
                             rotation(360.0f * t * 5.0f, Z) *
                             translation(0.0f, -80.0f, 0.0f));

glUniformMatrix4fv(model_matrix_pos, 1, GL_FALSE, m[0]);
glUniformMatrix4fv(projection_matrix_pos, 1, GL_FALSE, p);

// 关闭光栅化
glEnable(GL_RASTERIZER_DISCARD);
// 绑定 transform feedback 对象并开始记录信息（这里使用 GL_POINTS）
glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, xfb);
glBeginTransformFeedback(GL_POINTS);

// 渲染对象
object.Render();

// 停止记录并且解除 transform feedback 对象的绑定
glEndTransformFeedback();
glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);

// 开启光栅化
glDisable(GL_RASTERIZER_DISCARD);

static const vec4 colors[2] = {
        vec4(0.8f, 0.8f, 0.9f, 0.5f),
        vec4(0.3f, 1.0f, 0.3f, 0.8f)
};

// 使用新的渲染程序对象
glUseProgram(render_prog);

// 第二个过程——正常渲染朝向左侧的多边形
glUniform4fv(0, 1, colors[0]);
glBindVertexArray(vao[0]);
glDrawTransformFeedbackStream(GL_TRIANGLES, xfb, 0);

// 现在将绘制数据流 1，其中包含所有朝向右侧的多边形
glUniform4fv(0, 1, colors[1]);
glBindVertexArray(vao[1]);
glDrawTransformFeedbackStream(GL_TRIANGLES, xfb, 1);