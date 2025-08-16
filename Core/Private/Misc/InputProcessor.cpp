#include "Misc/InputProcessor.h"

InputProcessor::InputProcessor(GLFWwindow* window, Camera* camera)
    : Window(window), MainCamera(camera), LastX(400.0), LastY(300.0), FirstMouse(true)
{
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(Window, this);
    glfwSetScrollCallback(Window, ScrollCallback);
}

void InputProcessor::ProcessInput(float deltaTime)
{
    if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS) MainCamera->ProcessKeyboard(deltaTime, true, false, false, false);
    if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS) MainCamera->ProcessKeyboard(deltaTime, false, true, false, false);
    if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS) MainCamera->ProcessKeyboard(deltaTime, false, false, true, false);
    if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS) MainCamera->ProcessKeyboard(deltaTime, false, false, false, true);
    if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(Window, true);

    double xpos, ypos;
    glfwGetCursorPos(Window, &xpos, &ypos);

    if (FirstMouse)
    {
        LastX = xpos;
        LastY = ypos;
        FirstMouse = false;
    }

    float xOffset = static_cast<float>(xpos - LastX);
    float yOffset = static_cast<float>(LastY - ypos);

    LastX = xpos;
    LastY = ypos;

    MainCamera->ProcessMouse(xOffset, yOffset);
}

void InputProcessor::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    InputProcessor* input = static_cast<InputProcessor*>(glfwGetWindowUserPointer(window));
    if (!input) return;

    input->MainCamera->MovementSpeed += static_cast<float>(yOffset);

    // Ограничение значений скорости
    if (input->MainCamera->MovementSpeed < 0.1f) input->MainCamera->MovementSpeed = 0.1f;
    if (input->MainCamera->MovementSpeed > 20.0f) input->MainCamera->MovementSpeed = 20.0f;
}
