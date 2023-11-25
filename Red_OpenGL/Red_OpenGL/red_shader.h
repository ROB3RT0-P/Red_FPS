/*******************************************
    Written by Robert Parry [RJP] - 2023    
*******************************************/

#pragma once

#include "red_includes.h"

class Shader {
public:
    Shader();
    ~Shader();

    bool LoadShader(const char* vertexPath, const char* fragmentPath);
    void Use() const;

    GLuint GetProgramID() const;

private:
    GLuint programID;

    void CheckCompileErrors(GLuint shader, const std::string& type);
};

