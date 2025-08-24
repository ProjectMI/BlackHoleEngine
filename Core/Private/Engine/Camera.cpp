#include "Engine/Camera.h"

Camera::Camera()
    : Position(0.0f, 0.0f, 3.0f), Rotation(0.0f, -90.0f, 0.0f),
    MovementSpeed(2.5f), MouseSensitivity(0.1f)
{
}

glm::mat4 Camera::GetViewMatrix() const
{
    glm::vec3 front;
    front.x = cos(glm::radians(Rotation.Yaw)) * cos(glm::radians(Rotation.Pitch));
    front.y = sin(glm::radians(Rotation.Pitch));
    front.z = sin(glm::radians(Rotation.Yaw)) * cos(glm::radians(Rotation.Pitch));

    return glm::lookAt(
        glm::vec3(Position.X, Position.Y, Position.Z),
        glm::vec3(Position.X, Position.Y, Position.Z) + glm::normalize(front),
        glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::ProcessKeyboard(float deltaTime, bool forward, bool back, bool left, bool right)
{
    float velocity = MovementSpeed * deltaTime;

    glm::vec3 front;
    front.x = cos(glm::radians(Rotation.Yaw)) * cos(glm::radians(Rotation.Pitch));
    front.y = sin(glm::radians(Rotation.Pitch));
    front.z = sin(glm::radians(Rotation.Yaw)) * cos(glm::radians(Rotation.Pitch));
    glm::vec3 normalizedFront = glm::normalize(front);
    glm::vec3 rightVec = glm::normalize(glm::cross(normalizedFront, glm::vec3(0.0f, 1.0f, 0.0f)));

    if (forward) Position += Vector3D(normalizedFront * velocity);
    if (back)    Position -= Vector3D(normalizedFront * velocity);
    if (left)    Position -= Vector3D(rightVec * velocity);
    if (right)   Position += Vector3D(rightVec * velocity);
}

void Camera::ProcessMouse(float xOffset, float yOffset)
{
    xOffset *= MouseSensitivity;
    yOffset *= MouseSensitivity;

    Rotation.Yaw += xOffset;
    Rotation.Pitch += yOffset;

    if (Rotation.Pitch > 89.0f) Rotation.Pitch = 89.0f;
    if (Rotation.Pitch < -89.0f) Rotation.Pitch = -89.0f;
}

glm::mat4 Camera::GetBillboardMatrix(const glm::vec3& objectPos, glm::mat4& model) const
{
    glm::vec3 camPos = Position;
    glm::vec3 lookDir = glm::normalize(camPos - objectPos);
    glm::vec3 up(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(up, lookDir));
    glm::vec3 newUp = glm::normalize(glm::cross(lookDir, right));

    glm::mat4 rot(1.0f);
    rot[0] = glm::vec4(right, 0.0f);
    rot[1] = glm::vec4(newUp, 0.0f);
    rot[2] = glm::vec4(lookDir, 0.0f);

    // Трансляция объекта на своё место
    glm::mat4 trans = glm::translate(glm::mat4(1.0f), objectPos);

    return model = trans * rot;
}

