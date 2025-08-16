#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include "Shader.h"

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

protected:
    std::unique_ptr<Shader> ObjectShader;
    GLuint VAO = 0;
    GLuint VBO = 0;
    int VertexCount = 0;
};
