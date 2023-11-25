/*******************************************
    Written by Robert Parry [RJP] - 2023    
*******************************************/

#pragma once

#include "red_includes.h"
#include "red_camera.h"

class Input {
public:
    Input(GLFWwindow* window, Camera& camera);
    void ProcessInput(float deltaTime);

private:
    GLFWwindow* window;
    Camera& camera;

    bool firstMouse;
    float lastX;
    float lastY;

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
};
