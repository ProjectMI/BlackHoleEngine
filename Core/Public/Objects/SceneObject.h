#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "Misc/Shader.h"
#include "Mesh.h"

class SceneObject
{
public:
    SceneObject() = default;
    virtual ~SceneObject() = default;

    // запрет копирования, можно перемещать
    SceneObject(const SceneObject&) = delete;
    SceneObject& operator=(const SceneObject&) = delete;
    SceneObject(SceneObject&&) noexcept = default;
    SceneObject& operator=(SceneObject&&) noexcept = default;

    virtual void Draw(const glm::mat4& projection, const glm::mat4& view) = 0;
    void SetPosition(const Vector3D& pos) { Position = pos; UpdateModel(); }
    void SetRotation(const Rotator& rot) { Rotation = rot; UpdateModel(); }
    void SetScale(const Vector3D& sc) { Scale = sc;    UpdateModel(); }

    Vector3D GetPosition() const { return Position; }
    glm::vec3 GetPositionVec3() const { return Position; }
    Rotator  GetRotation() const { return Rotation; }
    Vector3D GetScale()    const { return Scale; }
    glm::mat4 GetModel() { return model; };
protected:
    void SetShader(const std::string& vertexPath, const std::string& fragmentPath);
    std::unique_ptr<Mesh> MeshObj;
    std::unique_ptr<Shader> ObjectShader;
    GLuint program;
    glm::mat4 model;

    Vector3D Position{ 0, 0, 0 };
    Rotator  Rotation{ 0, 0, 0 };
    Vector3D Scale{ 1, 1, 1 };

private:
    void UpdateModel();
};
