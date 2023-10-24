#pragma once

#include "red_includes.h"
#include <string>

class Shader {
public:
    Shader();
    ~Shader();

    bool Load(const char* vertexPath, const char* fragmentPath);
    void Use() const;
    GLuint GetProgramID() const;

    void SetUniform(const std::string& name, int value) const;
    void SetUniform(const std::string& name, float value) const;
    void SetUniform(const std::string& name, const Mat4& matrix) const;

private:
    GLuint programID;

    void CheckCompileErrors(GLuint shader, const std::string& type) const;
};
