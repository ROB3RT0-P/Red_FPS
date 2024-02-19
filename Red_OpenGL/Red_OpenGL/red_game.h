/*******************************************
    Written by Robert Parry [RJP] - 2023
    Refer to red_main.cpp for the license
*******************************************/

#pragma once
#include "red_includes.h"
#include "red_camera.h"


class Game {
public:
    Game();
    ~Game();
    void init();
   // void update(Camera& camera);
    void terminate();
    void run();
    int getExitCode() const;

private:
    GLFWwindow* window;
    int exitCode = 0;

    Renderer* renderer;
    Camera* camera;

    GLuint VAO, VBO;
};