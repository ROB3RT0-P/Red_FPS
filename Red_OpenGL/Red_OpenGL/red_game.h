/*******************************************
    Written by Robert Parry [RJP] - 2023
    Refer to red_main.cpp for the license
*******************************************/

#pragma once
#include "red_includes.h"
#include "red_camera.h"
#include "red_plane.h"


class Game {
public:
    Game();
    ~Game();
    void terminate();
    void init();
    void run();
    int getExitCode() const;

private:
    GLFWwindow* window;
    int exitCode = 0;

    Renderer* renderer;
    Camera* camera;
    Plane* plane;

};