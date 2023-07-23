//
// Created by leever on 2023/4/19.
//
/* 引入相应的库 */
#include <iostream>
#include <valarray>

using namespace std;
#define GLEW_STATIC
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include"Shader.h"

/* 编写各顶点位置 */
GLfloat vertices_1[] =
        {
                //position
                0.5f, 0.5f, 0.0f,			// top right		0
                0.5f, -0.5f, 0.0f,			// bottom right		1
                -0.5f, -0.5f, 0.0f,			// bottom left		2
                -0.5f, 0.5f, 0.0f,			// top left			3
        };

/* 四个顶点的连接信息给出来 */
GLuint indices_1[] =
        {
                0, 1, 3,		// 序号为 0、1、3 的顶点组合成一个三角形
                1, 2, 3			// 序号为 1、2、3 的顶点组合成一个三角形
        };

const GLint WIDTH = 600, HEIGHT = 600;		// 正方形窗口

int main()
{
    glfwInit();
    GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL Triangle test", nullptr, nullptr);
    int screenWidth_1, screenHeight_1;
    glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
    glfwMakeContextCurrent(window_1);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    /* 将我们自己设置的着色器文本传进来 */
    Shader ourShader = Shader("shader.vert", "shader.frag");		// 相对路径

    /* 设置顶点缓冲对象(VBO) + 设置顶点数组对象(VAO)  */
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

    /* 设置链接顶点属性 */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);	// 通道 0 打开

    /* 设置索引缓冲对象	*/
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_1), indices_1, GL_STATIC_DRAW);

    // draw loop 画图循环
    while (!glfwWindowShouldClose(window_1))
    {
        // 视口 + 时间
        glViewport(0, 0, screenWidth_1, screenHeight_1);
        glfwPollEvents();

        // 渲染 + 清除颜色缓冲
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*  绘制图形 */
        ourShader.Use();
        float time = glfwGetTime();						// 获取时间
        float redValue = sin(time) / 2.0f + 0.5f;		// 红色数值计算，范围[0,1]
        float greenValue = 1 - redValue;				// 绿色数值计算，范围[0.1]。且满足 “redValue + greenValue = 1”
        int vertexColorLocation = glGetUniformLocation(ourShader.Program, "time");
        glUniform4f(vertexColorLocation, redValue, greenValue, 0.0f, 1.0f );

        glBindVertexArray(VAO);									// 绑定 VAO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);				// 绑定 EBO
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// 画两个三角形 从第0个顶点开始 一共画6次
        glBindVertexArray(0);									// 解绑定 VAO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);				// 解绑定 EBO

        // 交换缓冲
        glfwSwapBuffers(window_1);
    }

    glDeleteVertexArrays(1, &VAO);	// 释放资源
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();				// 结束
    return 0;
}