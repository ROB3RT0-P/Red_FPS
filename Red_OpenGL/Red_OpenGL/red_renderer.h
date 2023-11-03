#pragma once

#include "red_shader.h"
#include "red_camera.h"
#include "red_includes.h"

class Renderer {
public:
    Renderer(int screenWidth, int screenHeight);
    ~Renderer();

    void Initialize();
    void Clear() const;
    void Render(const Shader& shader, const Camera& camera) const;
    void SetViewportSize(int width, int height);
    
private:
    int screenWidth;
    int screenHeight;
};
