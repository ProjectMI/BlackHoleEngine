#include "Engine/Engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

double Engine::fps = 0.0;

Engine::Engine(int width, int height, const char* title)
    : Width(width), Height(height), Title(title),
    Window(nullptr), DeltaTime(0.0f), LastFrame(0.0f)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window = glfwCreateWindow(Width, Height, Title, nullptr, nullptr);
    if (!Window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(Window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);

    MainCamera = std::make_unique<Camera>();
    Input = std::make_unique<InputProcessor>(Window, MainCamera.get());
    LastTime = glfwGetTime();
}

Engine::~Engine()
{
    glfwDestroyWindow(Window);
    glfwTerminate();
}

void Engine::Run()
{
    while (!glfwWindowShouldClose(Window))
    {
        ProcessDeltaTime();
        Input->ProcessInput(DeltaTime);

        RenderScene();

        ShowFPS();
    }
}

void Engine::AddObject(std::unique_ptr<SceneObject> object)
{
    SceneObjects.push_back(std::move(object));
}

SceneObject* Engine::GetObject(int index)
{
    return SceneObjects[index].get();
}

void Engine::ProcessDeltaTime()
{
    float currentFrame = static_cast<float>(glfwGetTime());
    DeltaTime = currentFrame - LastFrame;
    LastFrame = currentFrame;
}

void Engine::RenderScene()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)Width / (float)Height, 0.1f, 100.0f);
    glm::mat4 view = MainCamera->GetViewMatrix();

    for (auto& obj : SceneObjects)
        obj->Draw(projection, view);

    glfwSwapBuffers(Window);
    glfwPollEvents();
}

void Engine::ShowFPS()
{
    FrameCount++;
    currentTime = glfwGetTime();
    if (currentTime - LastTime >= 1.0) // раз в секунду
    {
        fps = double(FrameCount) / (currentTime - LastTime);
        std::string title = std::string(Title) + " | FPS: " + std::to_string((int)fps);
        glfwSetWindowTitle(Window, title.c_str());

        FrameCount = 0;
        LastTime = currentTime;
    }
}
