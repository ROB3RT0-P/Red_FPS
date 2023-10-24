#include "red_shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() : programID(0) {
}

Shader::~Shader() {
    if (programID) {
        glDeleteProgram(programID);
    }
}

bool Shader::Load(const char* vertexPath, const char* fragmentPath) {
    // Load and compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Read shader source from file, compile, and attach it to the program

    // Load and compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Read shader source from file, compile, and attach it to the program

    // Link the shaders into a program
    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    CheckCompileErrors(programID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

void Shader::Use() const {
    glUseProgram(programID);
}

GLuint Shader::GetProgramID() const {
    return programID;
}

void Shader::SetUniform(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

/*
void Shader::SetUniform(const std::string& name, const Mat4& matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}
*/
void Shader::CheckCompileErrors(GLuint shader, const std::string& type) const {
    GLint success;
    GLchar infoLog[1024];
    
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "Shader compilation error of type: " << type << "\n" << infoLog << "\n";
        }
    }
    else {
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(programID, 1024, NULL, infoLog);
            std::cerr << "Shader program linking error of type: " << type << "\n" << infoLog << "\n";
        }
    }
}
