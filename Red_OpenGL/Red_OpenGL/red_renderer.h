/*******************************************
    Written by Robert Parry [RJP] - 2023    
    Refer to red_main.cpp for the license
*******************************************/

#pragma once

#include "red_includes.h"

class Renderer {
public:
    Renderer(const char* vertexPath, const char* fragmentPath);
    ~Renderer();

    void exeShader() const;

private:
    GLuint programID;

    void compileShader(const char* source, GLuint shaderType);
};
