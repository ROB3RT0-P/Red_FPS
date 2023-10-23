#pragma once

#include <glew.h>
#include <glfw3.h>
#include <glm.h>
#include <matrix_transform.h>

class Camera {
public:
    Camera(GLFWwindow* window, GLfloat screenWidth, GLfloat screenHeight, glm::vec3 initialPosition = glm::vec3(0.0f, 0.0f, 0.0f));
    
    void ProcessKeyboard(GLfloat deltaTime);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

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

