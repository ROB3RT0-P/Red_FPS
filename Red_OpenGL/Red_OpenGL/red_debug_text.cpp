/*******************************************
    Written by Robert Parry [RJP] - 2023   
    Refer to red_main.cpp for the license 
*******************************************/

#include "red_debug_text.h"
#include "red_includes.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>\n"
"out vec3 Color;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"    gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"in vec3 Color;\n"
"out vec4 FragColor;\n"
"uniform vec3 textColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(textColor * Color, 1.0);\n"
"}\n\0";

DebugText::DebugText() : vao(0), vbo(0), program(0), posAttrib(0), colAttrib(0) {}

DebugText::~DebugText() 
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(program);
}

void DebugText::init() 
{
    // Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Link shaders
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glBindAttribLocation(program, 0, "vertex");
    glLinkProgram(program);

    // Delete shaders (no longer needed)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Get attribute locations
    posAttrib = glGetAttribLocation(program, "vertex");
    colAttrib = glGetAttribLocation(program, "Color");

    // Create VAO and VBO
    createBuffers();
}

void DebugText::createBuffers() 
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Set up vertex attributes
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0); // Unbind VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
}

GLuint DebugText::loadTextureAtlas(const char* imagePath) 
{

    if (!imagePath)
    {
        imagePath = ".../Textures/abc_atlus.png"; //default
    }

    // Load image using stb_image
    int width, height, channels;
    unsigned char* imageData = stbi_load(imagePath, &width, &height, &channels, STBI_rgb_alpha);
    if (!imageData) 
    {
        std::cerr << "Failed to load texture atlas image: " << imagePath << std::endl;
        return 0;
    }

    // Generate and bind texture object
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load texture data from image data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Free stb_image allocated memory
    stbi_image_free(imageData);

    return textureID;
}

void DebugText::renderText(const std::string& text, const Math::Vec3& position, float scale, const Math::Vec3& color) 
{
    glUseProgram(program);
    glUniform3f(glGetUniformLocation(program, "textColor"), color.x, color.y, color.z);
    glBindVertexArray(vao);

    float xpos = position.x;
    float ypos = position.y;

    for (char c : text) 
    {
        // Retrieve texture coordinates for the character 'c' from texture atlas
        // Assuming the texture atlas contains characters arranged in a grid
        const int atlasWidth = 10;
        const int atlasHeight = 10;
        const int charWidth = 1;
        const int charHeight = 1;
        const int charsPerRow = atlasWidth / charWidth;

        // Calculate the position of the character in the atlas grid
        int charIndex = static_cast<int>(c) - 32; // Assuming ASCII characters start from space character (ASCII 32)
        int row = charIndex / charsPerRow;
        int col = charIndex % charsPerRow;

        // Calculate the texture coordinates for the character
        float texX = static_cast<float>(col * charWidth) / atlasWidth;
        float texY = static_cast<float>(row * charHeight) / atlasHeight;

        // Define the vertices of the quad
        float x0 = xpos;
        float x1 = xpos + scale;
        float y0 = ypos;
        float y1 = ypos + scale;

        // Add vertices to the vertices vector
        vertices.push_back(x0); vertices.push_back(y0); vertices.push_back(0.0f); // Position
        vertices.push_back(texX); vertices.push_back(texY); // Texture coordinate

        vertices.push_back(x1); vertices.push_back(y0); vertices.push_back(0.0f); // Position
        vertices.push_back(texX + (static_cast<float>(charWidth) / atlasWidth)); vertices.push_back(texY); // Texture coordinate

        vertices.push_back(x1); vertices.push_back(y1); vertices.push_back(0.0f); // Position
        vertices.push_back(texX + (static_cast<float>(charWidth) / atlasWidth)); vertices.push_back(texY + (static_cast<float>(charHeight) / atlasHeight)); // Texture coordinate

        vertices.push_back(x0); vertices.push_back(y0); vertices.push_back(0.0f); // Position
        vertices.push_back(texX); vertices.push_back(texY); // Texture coordinate

        vertices.push_back(x1); vertices.push_back(y1); vertices.push_back(0.0f); // Position
        vertices.push_back(texX + (static_cast<float>(charWidth) / atlasWidth)); vertices.push_back(texY + (static_cast<float>(charHeight) / atlasHeight)); // Texture coordinate

        vertices.push_back(x0); vertices.push_back(y1); vertices.push_back(0.0f); // Position
        vertices.push_back(texX); vertices.push_back(texY + (static_cast<float>(charHeight) / atlasHeight)); // Texture coordinate

        // Advance the position for the next character
        xpos += scale;
    }

    // Upload vertices to VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    // Draw text
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 5); // 5 components per vertex (x, y, z, texX, texY)

    // Clear vertices vector
    vertices.clear();

    glBindVertexArray(0);
}