#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Camera.h"
#include "Misc/InputProcessor.h"
#include "Misc/Shader.h"
#include "Objects/SceneObject.h"

class Engine
{
public:
    Engine(int width, int height, const char* title);
    ~Engine();

    void Run();
    void AddObject(std::unique_ptr<SceneObject> object);
    SceneObject* GetObject(int index);
    Camera* GetCamera() { return MainCamera.get(); };
    int Width;
    int Height;
private:
    GLFWwindow* Window;
    const char* Title;

    float DeltaTime;
    float LastFrame;

    std::unique_ptr<Camera> MainCamera;
    std::unique_ptr<InputProcessor> Input;
    std::vector<std::unique_ptr<SceneObject>> SceneObjects;

    void ProcessDeltaTime();
    void RenderScene();

private:
    void ShowFPS();
    int FrameCount;
    double currentTime;
    double LastTime;
    double fps;
};
