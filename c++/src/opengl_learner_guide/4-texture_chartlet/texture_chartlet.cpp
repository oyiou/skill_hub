//
// Created by leever on 2023/4/19.
//
/* 引入相应的库 */
#include <iostream>
using namespace std;
#define GLEW_STATIC
#include"Shader.h"
#include"glad/glad.h"					// 注：这一部分要根据个人情况进行设定
#include"GLFW/glfw3.h"
#include"SOIL2/stb_image.h"
#include"SOIL2/SOIL2.h"

int width, height;

/* (样例一：木板) 编写各顶点位置  + 读取纹理 */
//GLfloat vertices_1[] =
//        {
//                //position				// color				// texture coords(纹理坐标)
//                0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		// 右上顶点		编号0
//                0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		// 右下顶点		编号1
//                -0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		// 左下顶点		编号2
//                -0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f		// 左上顶点		编号3
//        };
//unsigned char* image = SOIL_load_image("T_image4.png", &width, &height, 0, SOIL_LOAD_RGBA);			// 获取图片


/* (样例二：4只猫) 编写各顶点位置  + 读取纹理 */
GLfloat vertices_1[] =
{
	//position				// color				// texture coords(纹理坐标)
	1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		2.0f, 2.0f,		// 右上顶点		编号0
	1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		2.0f, 0.0f,		// 右下顶点		编号1
	-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		// 左下顶点		编号2
	-1.0f, 1.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 2.0f		// 左上顶点		编号3
};
unsigned char* image = SOIL_load_image("T_image3.png", &width, &height, 0, SOIL_LOAD_RGBA);			// 获取图片


/* 四个顶点的连接信息给出来 */
GLuint indices_1[] =
        {
                0, 1, 3,		// 序号为 0、1、3 的顶点组合成一个三角形
                1, 2, 3			// 序号为 1、2、3 的顶点组合成一个三角形
        };

const GLint WIDTH = 600, HEIGHT = 600;

int main()
{
    glfwInit();
    GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL Texture test", nullptr, nullptr);
    int screenWidth_1, screenHeight_1;
    glfwGetFramebufferSize(window_1, &screenWidth_1, &screenHeight_1);
    cout << "screenWidth_1 = " << screenWidth_1 << ", screenHeight = " << screenHeight_1 << endl;
    glfwMakeContextCurrent(window_1);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    /* 将我们自己设置的着色器文本传进来 */
    Shader ourShader = Shader("shader.vert", "shader.frag");		// 相对路径

    /* 设置顶点缓冲对象(VBO) + 设置顶点数组对象(VAO) + 索引缓冲对象(EBO)  */
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_1), indices_1, GL_STATIC_DRAW);

    /* 设置链接顶点属性 */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);	// 通道 0 打开
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);	// 通道 1 打开
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(6*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);	// 通道 2 打开


    /* 生成纹理 */
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);			// 读取图片信息
    glGenerateMipmap(GL_TEXTURE_2D);	// 多层渐进纹理
    SOIL_free_image_data(image);

    /* 纹理环绕方式 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// S 坐标
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);	// T 坐标

    /* 纹理过滤 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);		// 当纹理被放大时, 用 GL_LINEAR 方式过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		// 当纹理被缩小时, 用 GL_NEAREST 方式过滤

    /* 纹理单元：下一节重点使用 */
    ourShader.Use();	// don't forget to activate/use the shader before setting uniforms!
    int textureLocation = glGetUniformLocation(ourShader.Program, "ourTexture");	// 找到着色器中 uniform 属性的名为"ourTexture"的纹理的索引
    glUniform1i(textureLocation, 0);		// 告诉 OpenGL 的着色器采样器属于哪个纹理单元

    /* draw loop 画图循环 */
    while (!glfwWindowShouldClose(window_1))
    {
        /* 视口 + 时间 */
        glViewport(0, 0, screenWidth_1, screenHeight_1);
        glfwPollEvents();

        /* 渲染 + 清除颜色缓冲 */
        glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* 生成纹理 */
        glActiveTexture(GL_TEXTURE0);			// 激活 0 号纹理单元。最多 16 个通道
        glBindTexture(GL_TEXTURE_2D, texture);	// 绑定这个纹理到当前激活的纹理目标

        /* 绘制图形 */
        ourShader.Use();
        glBindVertexArray(VAO);									// 绑定 VAO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);				// 绑定 EBO
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	// 画两个三角形 从第0个顶点开始 一共画6次
        glBindVertexArray(0);									// 解绑定 VAO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);				// 解绑定 EBO
        glBindTexture(GL_TEXTURE_2D, 0);						// 解绑定 纹理

        /* 交换缓冲 */
        glfwSwapBuffers(window_1);
    }

    /* 释放资源 */
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();	// 结束
    return 0;
}