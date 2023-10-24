#pragma once

#include "red_includes.h"

class Camera {
public:
    Camera(GLFWwindow* window, GLfloat screenWidth, GLfloat screenHeight, Vec3 initialPosition);
    
    void ProcessKeyboard(GLfloat deltaTime);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

    Mat4 GetViewMatrix() const;
    Mat4 GetProjectionMatrix() const;

private:
    Vec3 position;
    Vec3 front;
    Vec3 up;
    Vec3 right;
    Vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat movementSpeed;
    GLfloat mouseSensitivity;
    GLfloat zoom;

    GLfloat screenWidth;
    GLfloat screenHeight;

    void UpdateCameraVectors();
    GLFWwindow* window;
};

