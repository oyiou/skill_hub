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
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glm/gtc/type_ptr.hpp"

/* 编写各顶点位置 */
GLfloat vertices_1[] =
        {
                //position				// color				// texture_1 coords(纹理坐标)
                1.0f, 3.0f, 0.0f,		1.0f, 0.0f, 0.0f,		1.0f, 2.0f,			// 右上顶点		编号0
                1.0f, -3.0, 0.0f,		0.0f, 1.0f, 0.0f,		1.0f, -1.0f,		// 右下顶点		编号1
                -1.0f, -3.0f, 0.0f,		0.0f, 0.0f, 1.0f,		0.0f, -1.0f,		// 左下顶点		编号2
                -1.0f, 3.0f, 0.0f,		0.0f, 0.0f, 0.0f,		0.0f, 2.0f			// 左上顶点		编号3
                // 这里纹理坐标的范围超过 (0, 0) 到 (1, 1) 的部分会被进行 “纹理环绕” 处理！！！
        };

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
    GLFWwindow* window_1 = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL Transform test", nullptr, nullptr);
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

    /* 读取纹理 */
    int width, height;
    unsigned char* image_1 = SOIL_load_image("T_snow1.png", &width, &height, 0, SOIL_LOAD_RGBA);			// 获取图片
    cout << "width = " << width << ", height = " << height <<endl;
    unsigned char* image_2 = SOIL_load_image("T_snow2.png", &width, &height, 0, SOIL_LOAD_RGBA);
    cout << "width = " << width << ", height = " << height <<endl;

    /* 生成纹理——雪花图1 */
    GLuint texture_1;
    glGenTextures(1, &texture_1);				// 生成纹理的数量为 1
    glBindTexture(GL_TEXTURE_2D, texture_1);	// 绑定在 GL_TEXTURE_2D 上
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_1);
    glGenerateMipmap(GL_TEXTURE_2D);	// 多层渐进纹理

    /* 生成纹理——雪花图2 */
    GLuint texture_2;
    glGenTextures(1, &texture_2);
    glBindTexture(GL_TEXTURE_2D, texture_2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_2);
    glGenerateMipmap(GL_TEXTURE_2D);	// 多层渐进纹理

    /* 释放图像内存 */
    SOIL_free_image_data(image_1);
    SOIL_free_image_data(image_2);

    /* 纹理环绕方式 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// S 坐标
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// T 坐标

    /* 纹理过滤 */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* 设置 uniform 变量 */
    ourShader.Use(); // don't forget to activate/use the shader before setting uniforms!
    glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture_1"), 0);
    glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture_2"), 1);

    int cnt = 0;				// 计数器
    int flag = 1;				// 纹理切换标志
    int N = 2000;				// N 越大，位移/交替的速度都会变慢
    /* draw loop 画图循环 */
    while (!glfwWindowShouldClose(window_1))
    {
        /* 视口 + 时间 */
        glViewport(0, 0, screenWidth_1, screenHeight_1);
        glfwPollEvents();

        /* 渲染 + 清除颜色缓冲 */
        glClearColor(0.5f, 0.8f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* 激活 + 绑定纹理 */
        glActiveTexture(GL_TEXTURE0);				// 激活 0 号纹理单元。最多 16 个通道
        glBindTexture(GL_TEXTURE_2D, texture_1);	// 绑定这个纹理到当前激活的纹理目标
        glActiveTexture(GL_TEXTURE1);				// 激活 1 号纹理单元。最多 16 个通道
        glBindTexture(GL_TEXTURE_2D, texture_2);	// 绑定这个纹理到当前激活的纹理目标

        /* 每一次循环引起的反应 */
        cnt = cnt + 1;		// 计数器加1
        if( cnt >= 2*N )
            cnt = 0;		// 设置重复循环
        if( cnt == 0 || cnt == N )
            flag = -flag;	// 设置纹理循环交替标志

        /* 平移变换的实现 */
        glm::mat4 firsrMatrix_1 = glm::mat4(1.0f); // 初始化为单位矩阵
        glm::mat4 transform_1 = glm::translate(firsrMatrix_1, glm::vec3(0.0f, 1.0f - cnt*1.0/N, 0.0f));

        /* 交替变换的实现 */
        int vertexColorLocation = glGetUniformLocation(ourShader.Program, "time");	// 找到 “time” 的索引
        if( flag == 1 )
            glUniform1f(vertexColorLocation, cnt*1.0/N );			// 从纹理1 逐渐交替到 纹理2
        else
            glUniform1f(vertexColorLocation, 2.0 - cnt*1.0/N );		// 从纹理2 逐渐交替到 纹理1

        // get matrix's uniform location and set matrix
        unsigned int transformLoc = glGetUniformLocation(ourShader.Program, "transform_1");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_1));

        /* 绘制图形 */
        //ourShader.Use();
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