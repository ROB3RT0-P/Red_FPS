#include "red_renderer.h"
#include <iostream>

Renderer::Renderer(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight), window(nullptr), camera(nullptr) {
}

Renderer::~Renderer() {
    Cleanup();
}

bool Renderer::Initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(screenWidth, screenHeight, "Doom FPS", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    glViewport(0, 0, screenWidth, screenHeight);

    if (!shader.Load("vertex_shader.glsl", "fragment_shader.glsl")) {
        std::cerr << "Failed to load shaders" << std::endl;
        return false;
    }

    // Initialize models and textures here

    return true;
}

void Renderer::Render() {
    // Clear the screen and set up rendering context
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.Use();
    
    if (camera) {
        // Set the camera view and projection matrices
        shader.SetUniform("view", camera->GetViewMatrix());
        shader.SetUniform("projection", camera->GetProjectionMatrix());
    }

    // Render game objects, models, and world here

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::Cleanup() {

    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}

void Renderer::SetCamera(Camera* camera) {
    this->camera = camera;
}

void Renderer::SetViewport(int width, int height) {
    glViewport(0, 0, width, height);
}

