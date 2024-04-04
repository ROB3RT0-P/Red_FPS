/*******************************************
    Written by Robert Parry [RJP] - 2023    
    Refer to red_main.cpp for the license
*******************************************/

#include "red_game.h"
#include "red_includes.h"

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

    renderer = new Renderer("Shaders/red_vertex_shader.glsl", "Shaders/red_fragment_shader.glsl");

    // RJP - Set GLFW callback functions
    glfwSetKeyCallback(window, Input::keyCallback);

    init();
}

Game::~Game() {
    delete renderer;
    delete camera;
    delete debugText;
    delete stateMachine;
    glfwTerminate();
}

void Game::init() {
    // RJP - Create a camera
    Math::Vec3 cameraPosition(0.0f, 0.0f, 3.0f);
    Math::Vec3 cameraUp(0.0f, 1.0f, 0.0f);
    float cameraYaw = -90.0f;
    float cameraPitch = 0.0f;
    camera = new Camera(cameraPosition, cameraUp, cameraYaw, cameraPitch);

    // RJP - State Machine for Game States
    stateMachine = new StateMachine();
    stateMachine->setState(GameState::MENU);

    // RJP - Debug Text
    debugText = new DebugText();
    debugText->init();
    const char* atlasDir = ".../Textures/abc_atlas.png";
    debugText->loadTextureAtlas( atlasDir );
}

void Game::start()
{
   
}

void Game::update()
{
    float deltaTime = static_cast<float>(glfwGetTime());

    // RJP - Game Loop
    while (!glfwWindowShouldClose(window)) 
    {
        stateMachine->executeState(this, deltaTime);
    }
}

void Game::menuRun()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (stateMachine->getState() == GameState::MENU && input->handleInput() == 1)
    {
        stateMachine->setState(GameState::PLAY);
    }
            
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer->exeShader();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Game::gameRun(float deltaTime) 
{
    if (stateMachine->getState() == GameState::PLAY && input->handleInput() == 1)
    {
        stateMachine->setState(GameState::PAUSE);
    }

    Input::exeMovement(*camera, deltaTime);

    Math::Mat4 viewMatrix = camera->getViewMatrix();

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer->exeShader();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Game::pauseRun()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (stateMachine->getState() == GameState::PAUSE && input->handleInput() == 2)
    {
        exitCode = 1;
    }

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Game::gameOverRun()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderer->exeShader();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Game::terminate()
{

}
 
int Game::getExitCode() const {
    return exitCode;
}