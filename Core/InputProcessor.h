#pragma once

#include <GLFW/glfw3.h>
#include "Camera.h"

class InputProcessor
{
public:
    InputProcessor(GLFWwindow* window, Camera* camera);

    void ProcessInput(float deltaTime);
    static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
private:
    GLFWwindow* Window;
    Camera* MainCamera;

    double LastX;
    double LastY;
    bool FirstMouse;
};
