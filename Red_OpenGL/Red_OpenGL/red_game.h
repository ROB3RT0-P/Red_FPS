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
        void update();
        void gameRun( float deltaTime );
        void menuRun();
        void pauseRun();
        void gameOverRun();
        int getExitCode() const;
    
    private:
        GLFWwindow* window;

        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Camera> camera;
        std::unique_ptr<DebugText> debugText;
        std::unique_ptr<StateMachine> stateMachine;
        std::unique_ptr<Input> input;
        std::unique_ptr<Plane> plane;

        int exitCode = 0;
};