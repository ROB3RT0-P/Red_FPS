#pragma once

#include "red_includes.h"

#pragma once

#include "red_includes.h"

class Plane {
public:
    Plane();
    void init();
    void render(const ShaderProgram& shader);
    void destroyObj();

private:
    GLuint VAO, VBO, EBO;
};
