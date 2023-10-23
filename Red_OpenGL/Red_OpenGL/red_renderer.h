#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "red_shader.h"
#include "red_camera.h"

class Renderer {
public:
    Renderer(int screenWidth, int screenHeight);
    ~Renderer();

    bool Initialize();
    void Render();
    void Cleanup();

    void SetCamera(Camera* camera);
    void SetViewport(int width, int height);

private:
    int screenWidth;
    int screenHeight;
    GLFWwindow* window;

    Shader shader;
    Camera* camera; 
};

