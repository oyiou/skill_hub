//
// Created by leever on 2023/5/10.
//
#include "opengl_programing_guide.h"

GLuint shader, program;

static const GLchar *source[] = {
        "#version 430 core\n"
        "\n"
        "// 输入布局限定符声明一个 16x16(x1) 的本地工作组\n"
        "layout (lcoal_size_x = 16, local_size_y = 16) in;\n"
        "\n"
        "void main() {\n"
        "    // 什么都不做\n"
        "}\n"
};

shader = glCreateShader(GL_COMPUTE_SHADER);
glShaderSource(shader, 1, source, NULL);
glCompileShader(shader);

program = glCreateProgram();
glAttachShader(program, shader);
glLinkProgram(program);