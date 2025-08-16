#include "Objects/Mesh.h"

Mesh::Mesh(const std::vector<Vector3D>& vertices)
{
    VertexCount = static_cast<int>(vertices.size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3D), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3D), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}

Mesh::Mesh(Mesh&& other) noexcept
{
    VAO = other.VAO;
    VBO = other.VBO;
    VertexCount = other.VertexCount;

    other.VAO = 0;
    other.VBO = 0;
    other.VertexCount = 0;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    if (this != &other)
    {
        if (VBO) glDeleteBuffers(1, &VBO);
        if (VAO) glDeleteVertexArrays(1, &VAO);

        VAO = other.VAO;
        VBO = other.VBO;
        VertexCount = other.VertexCount;

        other.VAO = 0;
        other.VBO = 0;
        other.VertexCount = 0;
    }
    return *this;
}

void Mesh::Bind() const
{
    glBindVertexArray(VAO);
}

void Mesh::Unbind() const
{
    glBindVertexArray(0);
}
