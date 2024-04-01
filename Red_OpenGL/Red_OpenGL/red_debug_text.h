#pragma once

#include <string>
#include "red_includes.h"

class DebugText {
public:
    DebugText();
    ~DebugText();

    void init();
    void renderText(const std::string& text, const Math::Vec3& position, float scale, const Math::Vec3& color);
    GLuint loadTextureAtlas(const char* imagePath);

private:
    GLuint vao, vbo;
    GLuint program;
    GLint posAttrib, colAttrib;
    std::vector<float> vertices;
    GLuint textureAtlasID;
    
    void createBuffers();
};
