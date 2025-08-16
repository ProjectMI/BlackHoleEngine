#pragma once

#include <GL/glew.h>
#include <vector>
#include "Misc/Utils.h"

class Mesh
{
public:
    Mesh(const std::vector<Vector3D>& vertices);
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    void Bind() const;
    void Unbind() const;
    int GetVertexCount() const { return VertexCount; }

private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    int VertexCount = 0;
};

