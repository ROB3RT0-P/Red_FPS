/*******************************************
    Written by Robert Parry [RJP] - 2023    
    Refer to red_main.cpp for the license
*******************************************/

#include "red_game.h"
#include "red_includes.h"
#include "red_camera.h"
#include "red_input.h"

const GLint WIDTH = 800, HEIGHT = 600;

Game::Game() {
    if (!glfwInit()) {
        exitCode = -1;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "RED", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exitCode = -1;
        return;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        exitCode = -1;
        return;
    }

    renderer = new Renderer("/Shaders/red_vertex_shader.glsl", "Shaders/red_fragment_shader.glsl");

    // Triangle vertices
    GLfloat vertices[] =
    {
        0.0f, 1.0f, 0.0f,
        -0.0f, -1.0f, 0.0f,
        0.5f, -1.0f, 0.0f
    };

    // Vertex buffer object (VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Create a camera
    Math::Vec3 cameraPosition(0.0f, 0.0f, 3.0f);
    Math::Vec3 cameraUp(0.0f, 1.0f, 0.0f);
    float cameraYaw = -90.0f;
    float cameraPitch = 0.0f;
    camera = new Camera(cameraPosition, cameraUp, cameraYaw, cameraPitch);

    // Set GLFW callback functions
    glfwSetKeyCallback(window, Input::keyCallback);
}

Game::~Game() {
    delete renderer;
    delete camera;

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
}

void Game::run() {
    while (!glfwWindowShouldClose(window)) {
        float deltaTime = 0.5f; // testing
        Input::exeMovement(*camera, deltaTime);

        Math::Mat4 viewMatrix = camera->getViewMatrix();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer->exeShader();

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Game::terminate()
{

}
 
int Game::getExitCode() const {
    return exitCode;
}