//
// Created by leever on 2023/4/20.
//
/* 引入相应的库 */
#include <iostream>
using namespace std;
#define GLEW_STATIC
#include"Shader.h"
#include"Camera.h"
#include"glad/glad.h"					// 注：这一部分要根据个人情况进行设定
#include"GLFW/glfw3.h"
#include"SOIL2/stb_image.h"
#include"SOIL2/SOIL2.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

/* 编写各顶点位置 */
float vertices_1[] = {
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
        -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,
};

const GLint WIDTH = 600, HEIGHT = 600;

bool keys[1024];				// 专门存储按过的键
Camera camera(glm::vec3(1.0f, 1.0f, -5.0f),glm::vec3(-1.0f, -1.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);		// 对键盘的响应函数
void Key_Movement();			// 与 Camera 类互动的函数
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

int main()
{
    /* 初始化 glfw */
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);						// 缩放关闭

    /* 窗口捕获与处理 */
    GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Key Test", nullptr, nullptr);
    int screenWidth_1, screenHeight_1;
    glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
    cout << "screenWidth_1 = " << screenWidth_1 << ", screenHeight_1 = " << screenHeight_1 << endl;
    glfwMakeContextCurrent(window_1);
    glfwSetKeyCallback(window_1, KeyCallback);		// 注册到 glfw 里面，会进行联动响应

    /* 初始化 glad */
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    /* 开启深度测试 */
    glEnable(GL_DEPTH_TEST);

    /* 将我们自己设置的着色器文本传进来 */
    Shader ourShader = Shader("shader.vert", "shader.frag");		// 相对路径

    /* 设置顶点缓冲对象(VBO) + 设置顶点数组对象(VAO) */
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

    /* 设置链接顶点属性 */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);	// 通道 0 打开
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);	// 通道 1 打开

    /* draw loop 画图循环 */
    while (!glfwWindowShouldClose(window_1))
    {

        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        /* 视口 + 时间 */
        glViewport(0, 0, screenWidth_1, screenHeight_1);
        glfwPollEvents();		// 获取键盘鼠标
        Key_Movement();			// 获取键盘的小动作

        /* 渲染 + 清除颜色缓冲 */
        glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* 绘制图形 */
        ourShader.Use();					// 调用着色器程序
        glBindVertexArray(VAO);				// 绑定 VAO
        for(int i = 0; i < 2; i++)			// 准备绘制两个正方体
        {
            glm::mat4 transform_1;
            glm::mat4 view_1 = camera.GetViewMatrix();	// 求得观察矩阵
            if( i == 0 )		// 大立方体
            {
                transform_1 = glm::translate(transform_1, glm::vec3(0.0f, 0.0f, 0.0f));
                float new_size = cos(currentTime) * 0.2f + 0.8f;
                transform_1 = glm::scale(transform_1, glm::vec3(new_size, new_size, new_size));
            }
            else				// 小立方体
            {
                transform_1 = glm::translate(transform_1, glm::vec3(0.0f, 1.0f, 0.0f));
                transform_1 = glm::rotate(transform_1, currentTime, glm::vec3(0.2f, 1.0f, 0.0f));
                transform_1 = glm::scale(transform_1, glm::vec3(0.15f, 0.15f, 0.15f));
            }

            glm::mat4 projection_1 = glm::perspective(glm::radians(45.0f), (float)screenWidth_1/(float)screenHeight_1, 0.1f, 100.0f);

            int transform_1_Location = glGetUniformLocation(ourShader.Program, "transform_1");
            glUniformMatrix4fv(transform_1_Location, 1, GL_FALSE, glm::value_ptr(transform_1));

            int projection_1_Location = glGetUniformLocation(ourShader.Program, "projection_1");
            glUniformMatrix4fv(projection_1_Location, 1, GL_FALSE, glm::value_ptr(projection_1));

            int view_1_Location = glGetUniformLocation(ourShader.Program, "view_1");
            glUniformMatrix4fv(view_1_Location, 1, GL_FALSE, glm::value_ptr(view_1));

            // 第一个参数在 vs.txt 中，第二个在主函数中
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);				// 解绑定 VAO

        /* 交换缓冲 */
        glfwSwapBuffers(window_1);
    }

    /* 释放资源 */
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();	// 结束
    return 0;
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        cout << "按下了关闭键 esc = "<< key << endl;
    }
    if( key >= 0 && key <= 1024 )
    {
        if( action == GLFW_PRESS )
            keys[key] = true;	// true 代表按下了键
        else if( action == GLFW_RELEASE )
            keys[key] = false;
    }
}

void Key_Movement()
{
    if( keys[GLFW_KEY_Q])		// 向前
        camera.ProcessKeyboard(FORWARD, deltaTime);

    if( keys[GLFW_KEY_E] )		// 向后
        camera.ProcessKeyboard(BACKWARD, deltaTime);

    if( keys[GLFW_KEY_A] )		// 向左
        camera.ProcessKeyboard(LEFT, deltaTime);

    if( keys[GLFW_KEY_D] )		// 向右
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if( keys[GLFW_KEY_W] )		// 向上
        camera.ProcessKeyboard(UPWARD, deltaTime);

    if( keys[GLFW_KEY_S] )		// 向下
        camera.ProcessKeyboard(DOWNWARD, deltaTime);
}