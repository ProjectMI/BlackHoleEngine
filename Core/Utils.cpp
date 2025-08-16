#include "Utils.h"

Vector3D::Vector3D()
    : X(0.0f), Y(0.0f), Z(0.0f)
{
}

Vector3D::Vector3D(float x, float y, float z)
    : X(x), Y(y), Z(z)
{
}

Vector3D::Vector3D(const glm::vec3& vec)
    : X(vec.x), Y(vec.y), Z(vec.z)
{
}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
    return Vector3D(X + other.X, Y + other.Y, Z + other.Z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
    return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
}

Vector3D& Vector3D::operator+=(const Vector3D& other)
{
    X += other.X;
    Y += other.Y;
    Z += other.Z;
    return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& other)
{
    X -= other.X;
    Y -= other.Y;
    Z -= other.Z;
    return *this;
}

Vector3D::operator glm::vec3() const
{
    return glm::vec3(X, Y, Z);
}

Rotator::Rotator()
    : Pitch(0.0f), Yaw(0.0f), Roll(0.0f)
{
}

Rotator::Rotator(float pitch, float yaw, float roll)
    : Pitch(pitch), Yaw(yaw), Roll(roll)
{
}