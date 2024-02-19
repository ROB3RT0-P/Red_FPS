/*******************************************
    Written by Robert Parry [RJP] - 2023    
    Refer to red_main.cpp for the license
*******************************************/

#pragma once

#include "red_includes.h"
#include "red_camera.h"

class Input {
public:
    static bool keys[1024];
    static GLfloat lastX;
    static GLfloat lastY;
    static bool firstMouse;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void mouseCallback(GLFWwindow* window, double xPos, double yPos, Camera& camera);
    static void setMouseCallback(GLFWwindow* window, Camera& camera);
    static void scrollCallBack(GLFWwindow* window, double xOffset, double yOffset, Camera& camera);
    static void exeMovement(Camera& camera, float deltaTime);
};
