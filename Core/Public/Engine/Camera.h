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
    glm::mat4 GetBillboardMatrix(const glm::vec3& objectPos, glm::mat4& model) const;
    glm::vec3 GetPositionVec3() const { return Position; }
    Vector3D Position;
    Rotator Rotation;
    float MovementSpeed;
    float MouseSensitivity;
};
