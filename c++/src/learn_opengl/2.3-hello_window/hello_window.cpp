//
// Created by leever on 2023/6/3.
//
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);

int main() {
    glfwInit(); // 初始化 GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);  // 次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 使用核心模式（Core-profile）
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // 如果使用的是 Mac OS X

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {  // 初始化 GLAD
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600); // 视口：设置窗口的维度

    void (*framebuffer_size_callback_ptr)(GLFWwindow*, int, int);
    framebuffer_size_callback_ptr = framebuffer_size_callback;
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback_ptr);  // 注册回调函数，每当窗口调整大小的时候调用这个函数

    // 渲染循环
    while (!glfwWindowShouldClose(window)) {    // 每次循环的开始前检查一次 GLFW 是否被要求退出
        processInput(window);   // 检测输入

        // 渲染指令
        // ...
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 检查并调用事件，交换缓冲
        glfwSwapBuffers(window);    // 交换颜色缓冲（它是一个存储着 GLFW 窗口每一个像素颜色值的大缓冲）
        glfwPollEvents();   // 检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
    }

    glfwTerminate();    // 渲染循环结束后正确释放/删除之前的分配的所有资源
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  // 检查是否按下返回键（Esc），如果没有按下将会返回 GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
}