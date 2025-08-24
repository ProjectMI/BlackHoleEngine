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

std::unique_ptr<Mesh> Mesh::CreateMesh(const std::vector<Vector3D>& vertices)
{
    return std::make_unique<Mesh>(vertices);
}

std::unique_ptr<Mesh> Mesh::CreateSphere(float radius)
{
    std::vector<Vector3D> verts;
    int latSegments = 64;
    int longSegments = 128;
    verts.reserve(latSegments * longSegments * 6);

    for (int y = 0; y < latSegments; ++y)
    {
        float v0 = float(y) / latSegments;
        float v1 = float(y + 1) / latSegments;
        float theta0 = v0 * M_PI;
        float theta1 = v1 * M_PI;

        for (int x = 0; x < longSegments; ++x)
        {
            float u0 = float(x) / longSegments;
            float u1 = float(x + 1) / longSegments;
            float phi0 = u0 * 2.0f * M_PI;
            float phi1 = u1 * 2.0f * M_PI;

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
    return CreateMesh(verts);
}

std::unique_ptr<Mesh> Mesh::CreateCircle(float radius)
{
    std::vector<Vector3D> verts;
    int segments = 64; // чем больше, тем "круглее"

    verts.reserve(segments * 3);

    Vector3D center(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < segments; ++i)
    {
        float theta0 = (float)i / segments * 2.0f * M_PI;
        float theta1 = (float)(i + 1) / segments * 2.0f * M_PI;

        Vector3D p0(radius * cos(theta0), radius * sin(theta0), 0.0f);
        Vector3D p1(radius * cos(theta1), radius * sin(theta1), 0.0f);

        // треугольник (центр, p0, p1)
        verts.emplace_back(center);
        verts.emplace_back(p0);
        verts.emplace_back(p1);
    }

    return CreateMesh(verts);
}


