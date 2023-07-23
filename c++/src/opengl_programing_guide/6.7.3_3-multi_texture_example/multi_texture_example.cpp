//
// Created by leever on 2023/4/21.
//
#include "opengl_programing_guide.h"

// prog 包括顶点和片元着色器的已链接程序的名称
glUseProgram(prog);
// 对于第一个纹理，使用纹理单元 0，得到 uniform 位置
GLint tex1_uniform_loc = glGetUniformLocation(prog, "tex1");
// 把它设置为 0
glUniform1i(tex1_uniform_loc, 0);
// 选择纹理单元 0
glActiveTexture(GL_TEXTURE0);
// 为它绑定纹理
glBindTexture(GL_TEXTURE_2D, tex1);
// 为纹理单元 1 重复上面的过程
GLint tex2_uniform_loc = glGetUniformLocation(prog, "tex2");
glUniform1i(tex2_uniform_loc, 1);
glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, tex2);