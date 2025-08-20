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
    static std::vector<Vector3D> CreateUVSphere(float radius, int latSegments = 24, int longSegments = 48);
private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    int VertexCount = 0;
};

