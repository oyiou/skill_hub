//
// Created by leever on 2023/4/20.
//
/* 引入相应的库 */
#include <iostream>
using namespace std;
#define GLEW_STATIC
#include"Shader.h"
#include"Camera.h"
#include "Point_Light.h"
#include"glad/glad.h"							// 注：这一部分要根据个人情况进行设定
#include"GLFW/glfw3.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"
#include"glm/gtx/rotate_vector.hpp"

/* 编写各顶点位置 */
float vertices_1[] = {
        // x、y、z 坐标				// color				// normal
        -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,	// red 红色面
        0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	// green 绿色面
        0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f, 	// blue 蓝色面(不是图中那种蓝)
        -0.5f,  0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,

        0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,	// yellow 黄色面
        0.5f,  0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,		1.0f, 1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f, 	// purple 紫色面
        0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,	// cyan 青蓝色面
        0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 1.0f,		0.0f, 1.0f, 0.0f
};

const GLint WIDTH = 600, HEIGHT = 600;

bool keys[1024];				// 专门存储按过的键
Camera camera(glm::vec3(1.0f, 1.0f, -5.0f), glm::vec3(-1.0f, -1.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void Key_Movement();
void square_Movement(GLfloat&, GLfloat&, GLfloat&);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 1.0f);
const double Shift_pix = 0.0005;					// 正方体移动速度
int main()
{
    /* 初始化 glfw */
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);		// 缩放关闭

    /* 窗口捕获与处理 */
    GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Light Test", nullptr, nullptr);
    int screenWidth_1, screenHeight_1;
    glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
    glfwMakeContextCurrent(window_1);
    glfwSetKeyCallback(window_1, KeyCallback);

    /* 初始化 glad + 光照生成 */
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    Point_Light my_light = Point_Light();

    /* 深度测试开启 */
    glEnable(GL_DEPTH_TEST);

    /* 将我们自己设置的着色器文本传进来 */
    Shader ourShader = Shader("shader.vert", "shader.frag");		// 相对路径
    Shader lightShader = Shader("light.vert", "light.frag");		// 相对路径

    /* 设置顶点缓冲对象(VBO) + 设置顶点数组对象(VAO) */
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);

    /* 设置链接顶点属性 */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);		// 通道 0 打开
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);		// 通道 1 打开
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);		// 通道 2 打开

    GLfloat up_down_move = 0.0f;		// 上下移动的变量
    GLfloat left_right_move = 0.0f;		// 左右移动的变量
    GLfloat front_back_move  = 0.0f;	// 前后移动的变量

    /* draw loop 画图循环 */
    while (!glfwWindowShouldClose(window_1))
    {
        /* 时间获取 */
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = (float)currentTime;

        /* 视口 +  键鼠捕获 */
        glViewport(0, 0, screenWidth_1, screenHeight_1);
        glfwPollEvents();		// 获取键盘鼠标
        Key_Movement();			// 获取键盘
        square_Movement(up_down_move, left_right_move, front_back_move );		// 正方体移动

        /* 渲染 + 清除颜色缓冲 */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* 光照绘制 */
        lightShader.Use();
        glm::mat4 my_transform = glm::mat4(1.0f);
        lightPos = glm::rotate(lightPos, glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f));		// 旋转
        my_transform = glm::translate(my_transform, lightPos);									// 平移
        my_transform = glm::scale(my_transform, glm::vec3(0.1f, 0.1f, 0.1f));					// 缩放
        glm::mat4 my_projection = glm::perspective(glm::radians(45.0f), (float)screenWidth_1 / (float)screenHeight_1, 0.1f, 100.0f);
        glm::mat4 my_view = camera.GetViewMatrix();	// 求得观察矩阵
        int my_transform_Location = glGetUniformLocation(lightShader.Program, "transform_2");
        glUniformMatrix4fv(my_transform_Location, 1, GL_FALSE, glm::value_ptr(my_transform));
        int my_projection_Location = glGetUniformLocation(lightShader.Program, "projection_2");
        glUniformMatrix4fv(my_projection_Location, 1, GL_FALSE, glm::value_ptr(my_projection));
        int my_view_Location = glGetUniformLocation(lightShader.Program, "view_2");
        glUniformMatrix4fv(my_view_Location, 1, GL_FALSE, glm::value_ptr(my_view));
        my_light.Draw(lightShader);

        /* 正方体绘制 */
        my_transform = glm::mat4(1.0f);		// 初始化是必要的
        ourShader.Use();					// 调用着色器程序
        glBindVertexArray(VAO);				// 绑定 VAO
        my_transform = glm::translate(my_transform, glm::vec3(left_right_move, up_down_move, front_back_move ));
        my_transform = glm::scale(my_transform, glm::vec3(0.5, 0.5, 0.5));
        my_projection = glm::perspective(glm::radians(45.0f), (float)screenWidth_1 / (float)screenHeight_1, 0.1f, 100.0f);
        my_view = camera.GetViewMatrix();
        my_transform_Location = glGetUniformLocation(ourShader.Program, "transform_1");
        glUniformMatrix4fv(my_transform_Location, 1, GL_FALSE, glm::value_ptr(my_transform));
        my_projection_Location = glGetUniformLocation(ourShader.Program, "projection_1");
        glUniformMatrix4fv(my_projection_Location, 1, GL_FALSE, glm::value_ptr(my_projection));
        my_view_Location = glGetUniformLocation(ourShader.Program, "view_1");
        glUniformMatrix4fv(my_view_Location, 1, GL_FALSE, glm::value_ptr(my_view));
        int LightPos_Location = glGetUniformLocation(ourShader.Program, "LightPos");
        glUniform3f(LightPos_Location, lightPos.x, lightPos.y, lightPos.z);
        int CameraPos_Location = glGetUniformLocation(ourShader.Program, "CameraPos");
        glUniform3f(CameraPos_Location, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        glDrawArrays(GL_TRIANGLES, 0, 36);	// 绘制 36 个点(正方体)
        glBindVertexArray(0);				// 解绑定 VAO
        glfwSwapBuffers(window_1);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)	// 按键捕获(固定函数格式)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void Key_Movement()		// Camera
{
    if (keys[GLFW_KEY_Q])		// 向前
        camera.ProcessKeyboard(FORWARD, deltaTime);

    if (keys[GLFW_KEY_E])		// 向后
        camera.ProcessKeyboard(BACKWARD, deltaTime);

    if (keys[GLFW_KEY_A])		// 向左
        camera.ProcessKeyboard(LEFT, deltaTime);

    if (keys[GLFW_KEY_D])		// 向右
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (keys[GLFW_KEY_W])		// 向上
        camera.ProcessKeyboard(UPWARD, deltaTime);

    if (keys[GLFW_KEY_S])		// 向下
        camera.ProcessKeyboard(DOWNWARD, deltaTime);
}

void square_Movement(GLfloat& up_down_move, GLfloat& left_right_move, GLfloat& front_back_move)	 // Square
{

    if (keys[GLFW_KEY_UP])		// 向上
    {
        up_down_move += Shift_pix;
    }

    if (keys[GLFW_KEY_DOWN])	// 向下
    {
        up_down_move -= Shift_pix;
    }

    if (keys[GLFW_KEY_LEFT])	// 向左
    {
        left_right_move += Shift_pix;
    }

    if (keys[GLFW_KEY_RIGHT])	// 向右
    {
        left_right_move -= Shift_pix;
    }

    if (keys[GLFW_KEY_F])		// 向前(按 F 键)
    {
        front_back_move += Shift_pix;
    }

    if (keys[GLFW_KEY_B])		// 向后(按 B 键)
    {
        front_back_move -= Shift_pix;
    }
}