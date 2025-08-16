#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
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

    void Draw(const glm::mat4& projection, const glm::mat4& view);

protected:
    void SetShader(const std::string& vertexPath, const std::string& fragmentPath);
    std::unique_ptr<Mesh> MeshObj;
    std::unique_ptr<Shader> ObjectShader;
    GLuint program;
    glm::mat4 model;

};
