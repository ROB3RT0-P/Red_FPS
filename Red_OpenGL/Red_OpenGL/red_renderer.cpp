/*******************************************
    Written by Robert Parry [RJP] - 2023    
*******************************************/

#include "red_renderer.h"

Renderer::Renderer(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight) {}

Renderer::~Renderer() {}

void Renderer::Initialize() {
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(const Shader& shader, const Camera& camera) const {
    // Set the shader program
    shader.Use();

    // Set the view and projection matrices
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), 
                                           static_cast<float>(screenWidth) / static_cast<float>(screenHeight), 
                                           0.1f, 100.0f);
    
    shader.SetUniform("view", view);
    shader.SetUniform("projection", projection);

    // Render your objects here
}

void Renderer::SetViewportSize(int width, int height) {
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
}
