/*******************************************
    Written by Robert Parry [RJP] - 2023    
*******************************************/

/******************************************************************************************
    [RED] License

    Educational Use License

    Copyright (c) [2023] [Robert Parry]

    Permission is hereby granted, free of charge, to any person obtaining a copy of
    this software and associated documentation files (the "Software"), to use the
    Software for educational purposes only, including without limitation the rights
    to view, study, and learn from the source code.

    Any use, reproduction, copying, modification, distribution, sublicensing, or 
    other exploitation of the Software, in whole or in part, is expressly prohibited 
    without the express written permission of the copyright holder.
    
    This notice may not be removed or altered from any source distribution.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
    INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
    PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE 
    USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************************/

/*******************************************
    // TODO: 
        // Priority
            // Test triangle
            // Main
            // Renderer
            // Camera
            // Controls/Input
            // Game
            // Debug Text
        // Non-Priority
            //
*******************************************/

#include "red_includes.h"
#include "red_camera.h"
#include "red_input.h"
#include "red_renderer.h"
#include "red_game.h"

int main() {
    Game* game = new Game();

    if (game->getExitCode() != 0) {
        return game->getExitCode();
    }

    game->start();
    game->update();
    game->terminate();

    return 0;
}