#pragma once

#include <glm/glm.hpp>

class Vector3D
{
public:
    float X;
    float Y;
    float Z;

    Vector3D();
    Vector3D(float x, float y, float z);
    Vector3D(const glm::vec3& vec);

    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    Vector3D& operator+=(const Vector3D& other);
    Vector3D& operator-=(const Vector3D& other);
    operator glm::vec3() const;
};

class Rotator
{
public:
    float Pitch;
    float Yaw;
    float Roll;

    Rotator();
    Rotator(float pitch, float yaw, float roll);
};
