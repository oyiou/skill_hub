//
// Created by leever on 2023/4/20.
//

#ifndef C_POINT_LIGHT_H
#define C_POINT_LIGHT_H
#include "Shader.h"
#include "glad/glad.h"				// 根据自身情况进行设置
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

GLfloat vertices_2[] =
        {	// 坐标
                // x、y、z 坐标				// color
                -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,	// red 红色面
                0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
                0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
                0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,	// green 绿色面
                0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,	// blue 蓝色面
                -0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,

                0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,	// yellow 黄色面
                0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
                0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
                0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,	// purple 紫色面
                0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,	// cyan 青色面
                0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f
        };

class Point_Light
{
public:
    Point_Light()				// 构造函数
    {
        this->update();
    }

    void Draw(Shader &shader)	// 绘制函数
    {
        glBindVertexArray(light_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }

    ~Point_Light()				// 析构函数
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &light_VAO);
        glDeleteBuffers(1, &light_VBO);
    }

private:
    GLuint light_VAO, light_VBO;
    void update()
    {
        /* 设置顶点缓冲对象(VBO) + 设置顶点数组对象(VAO) */
        glGenVertexArrays(1, &light_VAO);
        glGenBuffers(1, &light_VBO);
        glBindVertexArray(light_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, light_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);

        /* 设置链接顶点属性 */
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
    }
};

#endif //C_POINT_LIGHT_H
