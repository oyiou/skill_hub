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

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UPWARD,
    DOWNWARD
};

const GLfloat SPEED =  6.0f;

class Camera
{
public:
    /* 构造函数 */
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f) ,glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) :movementSpeed(SPEED)
    {
        this->position = position;
        this->camera_Z_axis = target;
        this->camera_Y_axis = up;
        this->camera_X_axis = glm::normalize(glm::cross(this->camera_Z_axis, this->camera_Y_axis));

        this->Zoom = 45.0f;
        this->Yaw = 90.0f;
        this->Pitch = 0.0f;
        this->MouseSensitivity = 0.2f;
        this->updateCameraVectors();
    }

    /* 观察矩阵 */
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(this->position, this->position + this->camera_Z_axis, this->camera_Y_axis);
    }

    /* 获取当前摄像机的视野(即观察空间的大小) */
    GLfloat GetZoom()
    {
        return this->Zoom;
    }

    /* 获取当前摄像机的位置 */
    glm::vec3 GetPosition()
    {
        return this->position;
    }

    /* 键盘控制的视角变化 */
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

    /* 鼠标移动的视角变化 */
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        /* 防止出现 “倒立看大地” 的情况 */
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }
        this->updateCameraVectors();
    }

    /* 鼠标滚轮缩放 */
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }


private:
    glm::vec3 position;
    glm::vec3 camera_Z_axis;
    glm::vec3 camera_X_axis;
    glm::vec3 camera_Y_axis;
    GLfloat movementSpeed;

    float Yaw;              // 俯仰角
    float Pitch;            // 偏移角
    float MouseSensitivity; // 鼠标灵敏度
    float Zoom;             // 投影深度

    void updateCameraVectors()
    {
        /* 鼠标移动 */
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        this->camera_Z_axis= front;

        /* 摄像机的坐标系 */
        this->camera_Z_axis = glm::normalize(this->camera_Z_axis);
        this->camera_X_axis = glm::normalize(glm::cross(this->camera_Z_axis, this->camera_Y_axis));
        this->camera_Y_axis = glm::normalize(glm::cross(this->camera_X_axis, this->camera_Z_axis));
    }
};

#endif //C_CAMERA_H
