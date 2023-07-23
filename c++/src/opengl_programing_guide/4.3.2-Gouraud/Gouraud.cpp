//
// Created by leever on 2023/3/31.
//
#include <iostream>
using namespace std;

#include "vgl.h"
#include "LoadShaders.h"

enum VAO_IDs {Triangles, NumVAOs};
enum Buffer_IDs {ArrayBuffer, NumBuffers};
enum Attrib_IDs {vPosition = 0, vColor = 1};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

// init
void init(void) {
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    struct VertexData {
        GLubyte color[4];
        GLfloat position[4];
    };

    VertexData vertices[NumVertices] = {
            {{255,  0,  0,  255}, {-0.90,   -0.90}},    // 三角形1
            {{0,  255,  0,  255}, {0.85,   -0.90}},
            {{0,  0,  255,  255}, {-0.90,   0.85}},
            {{10,  10,  10,  255}, {0.90,   -0.85}},    // 三角形2
            {{100,  100,  100,  255}, {0.90,   0.90}},
            {{255,  255,  255,  255}, {-0.85,   0.90}},
    };

    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, "Gouraud.vert"},
            {GL_FRAGMENT_SHADER, "Gouraud.frag"},
            {GL_NONE, NULL},
    };

    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    glVertexAttribPointer(vColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexData), BUFFER_OFFSET(0));
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), BUFFER_OFFSET(sizeof(vertices[0].color)));

    glEnableVertexAttribArray(vColor);
    glEnableVertexAttribArray(vPosition);
}