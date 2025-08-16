#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Misc/Utils.h"

class Camera
{
public:
    Camera();

    glm::mat4 GetViewMatrix() const;
    void ProcessKeyboard(float deltaTime, bool forward, bool back, bool left, bool right);
    void ProcessMouse(float xOffset, float yOffset);

    Vector3D Position;
    Rotator Rotation;
    float MovementSpeed;
    float MouseSensitivity;
};
