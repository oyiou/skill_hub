//
// Created by leever on 2023/4/18.
//
/* 第一步：引入相应的库 */
#include <iostream>
using namespace std;
#define GLEW_STATIC
#include "glad/glad.h"
#include <GLFW/glfw3.h>


/* 第二步：编写顶点位置 */
GLfloat vertices_1[] =
        {
                0.0f, 0.5f, 0.0f,		// 上顶点
                -0.5f, -0.5f, 0.0f,		// 左顶点
                0.5f, -0.5f, 0.0f,		// 右顶点

        };


/* 第三步：编写顶点着色器 */
const GLchar* vertexCode_1 = "#version 330 core\n"		// 3.30版本
                             "layout(location = 0) in vec3 position_1;\n"			// 三个浮点数vector向量表示位置 position变量名
                             "void main()\n"
                             "{\n"
                             "gl_Position = vec4(position_1, 1.0f);\n"				// 核心函数(位置信息赋值)
                             "}\n";


/* 第四步：编写片元着色器(也称片段着色器) */
const GLchar* fragmentCode_1 = "#version 330 core\n"	// 版本信息
                               "out vec4 FragColor_1;\n"								//输出是四个浮点数构成的一个向量 RGB+aerfa
                               "void main()\n"
                               "{\n"
                               "FragColor_1 = vec4(0.5f, 0.75f, 0.25f, 1.0f);\n"
                               "}\n";

const GLint WIDTH = 800, HEIGHT = 600;

// DrawArray 、 VAO 这两个要重点理解，其他只要知道大致模块功能就行了。

int main()
{
    glfwInit();
    GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL Triangle test", nullptr, nullptr);

    int screenWidth_1, screenHeight_1;
    glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
    glfwMakeContextCurrent(window_1);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


    /* 第三步：编写顶点着色器 */
    GLuint vertexShader_1 = glCreateShader(GL_VERTEX_SHADER);		// 创建顶点着色器对象
    glShaderSource(vertexShader_1, 1, &vertexCode_1, NULL);			// 将顶点着色器的内容传进来
    glCompileShader(vertexShader_1);	// 编译顶点着色器
    GLint flag;							// 用于判断编译是否成功
    GLchar infoLog[512];				// 512个字符
    glGetShaderiv(vertexShader_1, GL_COMPILE_STATUS, &flag); // 获取编译状态
    if( !flag )
    {
        glGetShaderInfoLog(vertexShader_1, 512, NULL, infoLog);   // 缓冲池
        cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog<<endl;
    }


    /* 第四步：编写片元着色器(也称片段着色器) */
    GLuint fragmentShader_1 = glCreateShader(GL_FRAGMENT_SHADER);		// 创建片元着色器对象
    glShaderSource(fragmentShader_1, 1, &fragmentCode_1, NULL);			// 将顶点着色器的内容传进来
    glCompileShader(fragmentShader_1);									// 编译顶点着色器
    glGetShaderiv(fragmentShader_1, GL_COMPILE_STATUS, &flag);			// 获取编译状态
    if( !flag )
    {
        glGetShaderInfoLog(fragmentShader_1, 512, NULL, infoLog);		// 缓冲池
        cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<infoLog<<endl;
    }


    /* 第五步：创建着色器程序 */
    GLuint shaderProgram_1 = glCreateProgram();
    glAttachShader(shaderProgram_1, vertexShader_1);
    glAttachShader(shaderProgram_1, fragmentShader_1);
    glLinkProgram(shaderProgram_1);
    glGetProgramiv(shaderProgram_1, GL_LINK_STATUS, &flag);
    if( !flag )
    {
        glGetProgramInfoLog(shaderProgram_1, 512, NULL, infoLog);
        cout<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog<<endl;
    }
    glDeleteShader(vertexShader_1);
    glDeleteShader(fragmentShader_1);


    /* 第七步：设置顶点缓冲对象(VBO) + 第八步：设置顶点数组对象(VAO)  */
    GLuint VAO, VBO;				// 它俩是成对出现的
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);	// 从显卡中划分一个空间出来
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);	// GL_STATIC_DRAW：静态的画图(频繁地读)


    /* 第六步：设置链接顶点属性 */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);


    // draw loop 画图循环
    while (!glfwWindowShouldClose(window_1))
    {
        glViewport(0, 0, screenWidth_1, screenHeight_1);
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /*  第九步：绘制三角形 */
        glUseProgram(shaderProgram_1);		// 渲染调用着色器程序
        glBindVertexArray(VAO);				// 绑定 VAO
        glDrawArrays(GL_TRIANGLES, 0, 3);	// 画三角形  从第0个顶点开始 一共画3次
        glBindVertexArray(0);				// 解绑定

        glfwSwapBuffers(window_1);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram_1);

    glfwTerminate();
    return 0;
}