#include "Objects/Grid.h"
#include <iostream>


Grid::Grid(int size, float step, BlackHole* blackHole, float maxDepth) : BH(blackHole)
{
    std::vector<Vector3D> vertices;
    int dim = size * 2 + 1;

    for (int i = -size; i <= size; i++)
    {
        for (int j = -size; j <= size; j++)
        {
            float x = i * step;
            float z = j * step;
            float y = ComputeDeformation(x, z, maxDepth);
            vertices.emplace_back(x, y, z);
        }
    }

    std::vector<Vector3D> triangles = GenerateTriangles(vertices, dim);
    MeshObj = std::make_unique<Mesh>(triangles);
    SetShader("vertex.glsl", "grid_fragment.glsl");
}

void Grid::Draw(const glm::mat4& projection, const glm::mat4& view)
{
    ObjectShader->Use();
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    MeshObj->Bind();
    glDrawArrays(GL_LINES, 0, MeshObj->GetVertexCount());
    MeshObj->Unbind();
}

float Grid::ComputeDeformation(float x, float z, float maxDepth)
{
    float R = BH->GetRadius();
    Vector3D BHCoord = BH->GetPosition();
    float centerX = BHCoord.X;
    float centerZ = BHCoord.Z;

    float dx = x - centerX;
    float dz = z - centerZ;
    float dist = std::sqrt(dx * dx + dz * dz);

    float y = 0.0f;

    if (dist <= R)
    {
        // от центра до радиуса R: интерполируем от maxDepth до 0.3*maxDepth
        float t = dist / R; // 0..1
        y = -maxDepth * (1.0f - 0.7f * t); // линейна€ интерпол€ци€: maxDepth -> 0.3*maxDepth
    }
    else if (dist <= 2.f * R)
    {
        // от радиуса R до 2*R: интерпол€ци€ 0.3*maxDepth -> 0
        float t = (dist - R) / R;
        y = -maxDepth * 0.3f * (1.0f - t);
    }

    return y;
}

std::vector<Vector3D> Grid::GenerateTriangles(const std::vector<Vector3D>& vertices, int dim)
{
    std::vector<Vector3D> triangles;
    for (int i = 0; i < dim - 1; i++)
    {
        for (int j = 0; j < dim - 1; j++)
        {
            int idx = i * dim + j;
            Vector3D v0 = vertices[idx];
            Vector3D v1 = vertices[idx + 1];
            Vector3D v2 = vertices[idx + dim];
            Vector3D v3 = vertices[idx + dim + 1];

            // первый треугольник
            triangles.push_back(v0);
            triangles.push_back(v2);
            triangles.push_back(v1);

            // второй треугольник
            triangles.push_back(v1);
            triangles.push_back(v2);
            triangles.push_back(v3);
        }
    }
    return triangles;
}

