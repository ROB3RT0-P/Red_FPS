/*******************************************
    Written by Robert Parry [RJP] - 2023    
    Refer to red_main.cpp for the license
*******************************************/

#include "red_input.h"
#include "red_camera.h"
#include <iostream>

bool Input::keys[1024];
GLfloat Input::lastX = 400, Input::lastY = 300;
bool Input::firstMouse = true;

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
}

void Input::mouseCallback(GLFWwindow* window, double xPos, double yPos, Camera& camera)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    camera.processMouseMovement(xOffset, yOffset);
}


void Input::scrollCallBack(GLFWwindow* window, double xOffset, double yOffset, Camera& camera)
{
    camera.processMouseScroll(yOffset);
}


void Input::exeMovement(Camera& camera, float deltaTime)
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.processKeyboard(GLFW_KEY_W, deltaTime);
        std::cout << "Up";
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.processKeyboard(GLFW_KEY_S, deltaTime);
        std::cout << "Down";
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.processKeyboard(GLFW_KEY_A, deltaTime);
        std::cout << "Left";
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.processKeyboard(GLFW_KEY_D, deltaTime);
        std::cout << "Right";
    }
}

int Input::handleInput()
{
    for (int key : {GLFW_KEY_ENTER, GLFW_KEY_ESCAPE})
    {
        if (keys[key])
        {
            return key == GLFW_KEY_ENTER ? 1 : 2;
        }
    }
    return 0;
}