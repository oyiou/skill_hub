//
// Created by leever on 2023/4/20.
//

#ifndef C_CAMERA_H
#define C_CAMERA_H

#include <iostream>
using namespace std;
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum Camera_Movement {		// 枚举类型
    FORWARD,		// 向前
    BACKWARD,		// 向后
    LEFT,			// 向左
    RIGHT,			// 向右
    UPWARD,			// 向上
    DOWNWARD		// 向下
};

const GLfloat SPEED =  6.0f;	// 初始速度

class Camera
{
public:
    // 构造函数
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f) ,glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) :movementSpeed(SPEED)
    {
        this->position = position;
        this->camera_Z_axis = target;
        this->camera_Y_axis = up;
        this->camera_X_axis = glm::normalize(glm::cross(this->camera_Z_axis, this->camera_Y_axis));
        this->updateCameraVectors();		// 实时更新
    }

    // 观察矩阵
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(this->position, this->position + this->camera_Z_axis, this->camera_Y_axis);
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = this->movementSpeed * deltaTime;
        if(direction == FORWARD)
            this->position += this->camera_Z_axis * velocity;

        if(direction == BACKWARD)
            this->position -= this->camera_Z_axis * velocity;

        if(direction == LEFT)
            this->position -= this->camera_X_axis * velocity;

        if(direction == RIGHT)
            this->position += this->camera_X_axis * velocity;

        if(direction == UPWARD)
            this->position += this->camera_Y_axis * velocity;

        if(direction == DOWNWARD)
            this->position -= this->camera_Y_axis * velocity;
    }

    glm::vec3 GetPosition()		// 下一篇文章使用
    {
        return this->position;
    }

private:
    // 摄影机的属性
    glm::vec3 position;				// 相机当前位置
    glm::vec3 camera_Z_axis;		// 摄影机的 Z 轴向量
    glm::vec3 camera_X_axis;		// 摄影机的 X 轴向量
    glm::vec3 camera_Y_axis;		// 摄影机的 Y 轴向量
    GLfloat movementSpeed;			// 镜头移动速度

    void updateCameraVectors()
    {
        this->camera_Z_axis = glm::normalize(this->camera_Z_axis);
        this->camera_X_axis = glm::normalize(glm::cross(this->camera_Z_axis, this->camera_Y_axis));
        this->camera_Y_axis = glm::normalize(glm::cross(this->camera_X_axis, this->camera_Z_axis));
    }
};

#endif //C_CAMERA_H
