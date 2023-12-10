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
    TODO:
*******************************************/

#include "red_includes.h"

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "My GLFW Window", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Cleanup and exit
    glfwTerminate();
    return 0;
}