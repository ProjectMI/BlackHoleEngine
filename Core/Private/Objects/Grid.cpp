#include "Objects/Grid.h"


Grid::Grid(int size, float step)
{
    std::vector<Vector3D> vertices;
    vertices.reserve((size * 2 + 1) * 4); // оптимизация

    for (int i = -size; i <= size; i++)
    {
        // линии вдоль Z
        vertices.emplace_back(i * step, 0.0f, -size * step);
        vertices.emplace_back(i * step, 0.0f, size * step);

        // линии вдоль X
        vertices.emplace_back(-size * step, 0.0f, i * step);
        vertices.emplace_back(size * step, 0.0f, i * step);
    }

    MeshObj = std::make_unique<Mesh>(vertices);

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

