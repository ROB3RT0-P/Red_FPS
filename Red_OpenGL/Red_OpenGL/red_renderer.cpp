/*******************************************
    Written by Robert Parry [RJP] - 2023    
    Refer to red_main.cpp for the license
*******************************************/

#include "red_renderer.h"

Renderer::Renderer(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        std::stringstream vShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        vShaderFile.close();
        vertexCode = vShaderStream.str();
    }
    catch (std::ifstream::failure&)
    {
        std::cerr << "VERTEX_SHADER_ERROR::UNSUCCESSFUL_READ" << std::endl;
    }

    try
    {
        fShaderFile.open(fragmentPath);
        std::stringstream fShaderStream;
        fShaderStream << fShaderFile.rdbuf();
        fShaderFile.close();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure&)
    {
        std::cerr << "FRAGMENT_SHADER_ERROR::UNSUCCESSFUL_READ" << std::endl;
    }

    if (vShaderFile && fShaderFile)
    {
        const char* vVertexCode = vertexCode.c_str();
        const char* fFragmentCode = fragmentCode.c_str();

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLenum vertexError = glGetError();
        if (vertexError != GL_NO_ERROR) 
        {
            std::cerr << "ERROR::OpenGL::glCreateShader(GL_VERTEX_SHADER): " << vertexError << std::endl;
        }
        glShaderSource(vertexShader, 1, &vVertexCode, nullptr);
        compileShader("Vertex", vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        GLenum fragmentError = glGetError();
        if (fragmentError != GL_NO_ERROR) 
        {
            std::cerr << "ERROR::OpenGL::glCreateShader(GL_FRAGMENT_SHADER): " << fragmentError << std::endl;
        }
        glShaderSource(fragmentShader, 1, &fFragmentCode, nullptr);
        compileShader("Fragment", fragmentShader);

        programID = glCreateProgram();
        glAttachShader(programID, vertexShader);
        glAttachShader(programID, fragmentShader);
        glLinkProgram(programID);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
}

Renderer::~Renderer()
{
    glDeleteProgram(programID);
}

void Renderer::exeShader()
{
    glUseProgram(programID);
}

void Renderer::compileShader(const char* shaderType, GLuint shader)
{
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}