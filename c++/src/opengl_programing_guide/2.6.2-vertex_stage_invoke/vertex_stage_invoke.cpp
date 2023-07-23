//
// Created by leever on 2023/3/27.
//
#include "opengl_programing_guide.h"

int main() {
    GLint materialShaderLoc;
    GLuint ambientIndex;
    GLuint diffuserIndex;

    glUseProgram(program);

    materialShaderLoc = glGetSubroutineUniformLocation(program, GL_VERTEX_SHADER, "materialShaderLoc");

    if (materialShaderLoc < 0) {
        // 错误：materialShaderLoc 不是着色器中启用的子程序 uniform
    }

    ambientIndex = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "ambient");
    diffuserIndex = glGetSubroutineIndex(program, GL_VERTEX_SHADER, "diffuser");
    if (ambientIndex == GL_INVALID_INDEX || diffuserIndex == GL_INVALID_INDEX) {
        // 错误：指定的子程序在 GL_VERTEX_SHADER 阶段当前绑定的程序中没有启用
    } else {
        GLsizei n;
        glGetIntegerv(GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS, &n);

        GLuint *indices = new GLuint [n];
        indices[materialShaderLoc] = ambientIndex;

        gl3wUniformSubroutinesuiv(GL_VERTEX_SHADER, n, indices);

        delete [] indices;
    }
}