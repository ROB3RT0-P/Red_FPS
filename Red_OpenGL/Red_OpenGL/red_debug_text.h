#pragma once

#include <string>
#include "red_includes.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class DebugText {
public:
    DebugText();
    ~DebugText();

    void init();
    void renderText(const std::string& text, const Math::Vec3& position, float scale, const Math::Vec3& color);

private:
    GLuint vao, vbo;
    GLuint program;
    GLint posAttrib, colAttrib;
    std::vector<float> vertices;
    GLuint textureAtlasID;

    void createBuffers();
    GLuint loadTextureAtlas(const char* imagePath);
};
