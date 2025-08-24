#pragma once

#include <GL/glew.h>
#include <memory>
#include <vector>
#include "Misc/Utils.h"

#define M_PI 3.141592653f

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
    static std::unique_ptr<Mesh> CreateMesh(const std::vector<Vector3D>& vertices);
    static std::unique_ptr<Mesh> CreateSphere(float radius);
    static std::unique_ptr<Mesh> CreateCircle(float radius);
private:
    GLuint VAO = 0;
    GLuint VBO = 0;
    int VertexCount = 0;
};

