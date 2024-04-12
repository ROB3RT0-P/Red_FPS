/*******************************************
    Written by Robert Parry [RJP] - 2023    
    Refer to red_main.cpp for the license
*******************************************/

#pragma once

#include "red_includes.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>

class ShaderProgram {
public:
    ShaderProgram();
    ShaderProgram(const char* vertexPath, const char* fragmentPath);
    ~ShaderProgram();

    void use() const;
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

private:
    GLuint ID;
    void checkCompileErrors(GLuint shader, const std::string& type);
};
