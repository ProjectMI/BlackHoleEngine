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

std::vector<Vector3D> Mesh::CreateUVSphere(float radius, int latSegments, int longSegments)
{
    std::vector<Vector3D> verts;
    verts.reserve(latSegments * longSegments * 6);

    float pi = 3.141592653f;

    for (int y = 0; y < latSegments; ++y)
    {
        float v0 = float(y) / latSegments;
        float v1 = float(y + 1) / latSegments;
        float theta0 = v0 * pi;
        float theta1 = v1 * pi;

        for (int x = 0; x < longSegments; ++x)
        {
            float u0 = float(x) / longSegments;
            float u1 = float(x + 1) / longSegments;
            float phi0 = u0 * 2.0f * pi;
            float phi1 = u1 * 2.0f * pi;

            // 4 вершины квадрата на сфере
            glm::vec3 p00(
                radius * sin(theta0) * cos(phi0),
                radius * cos(theta0),
                radius * sin(theta0) * sin(phi0)
            );
            glm::vec3 p10(
                radius * sin(theta1) * cos(phi0),
                radius * cos(theta1),
                radius * sin(theta1) * sin(phi0)
            );
            glm::vec3 p11(
                radius * sin(theta1) * cos(phi1),
                radius * cos(theta1),
                radius * sin(theta1) * sin(phi1)
            );
            glm::vec3 p01(
                radius * sin(theta0) * cos(phi1),
                radius * cos(theta0),
                radius * sin(theta0) * sin(phi1)
            );

            // два треугольника
            verts.emplace_back(p00.x, p00.y, p00.z);
            verts.emplace_back(p10.x, p10.y, p10.z);
            verts.emplace_back(p11.x, p11.y, p11.z);

            verts.emplace_back(p00.x, p00.y, p00.z);
            verts.emplace_back(p11.x, p11.y, p11.z);
            verts.emplace_back(p01.x, p01.y, p01.z);
        }
    }
    return verts;
}
