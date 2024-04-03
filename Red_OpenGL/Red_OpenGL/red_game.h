/*******************************************
    Written by Robert Parry [RJP] - 2023
    Refer to red_main.cpp for the license
*******************************************/

#pragma once

#include "red_includes.h"
#include "red_camera.h"
#include "red_plane.h"
#include "red_input.h"
#include "red_debug_text.h"
#include "red_state_machine.h"

class Game 
{
    public:
        Game();
        ~Game();
        void terminate();
        void init();
        void start();
        void gameRun();
        void menuRun();
        void pauseRun();
        void gameOverRun();
        int getExitCode() const;
    
    private:
        GLFWwindow* window;
        Renderer* renderer;
        Camera* camera;
        Plane* plane;
        DebugText* debugText;
        StateMachine* stateMachine;
        Input* input;

        int exitCode = 0;
};