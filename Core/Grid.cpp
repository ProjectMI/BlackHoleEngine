#include "Grid.h"
#include <glm/gtc/type_ptr.hpp>

Grid::Grid(int size, float step)
{
    std::vector<float> vertices;
    for (int i = -size; i <= size; i++)
    {
        // линии вдоль Z
        vertices.push_back(i * step); vertices.push_back(0.0f); vertices.push_back(-size * step);
        vertices.push_back(i * step); vertices.push_back(0.0f); vertices.push_back(size * step);

        // линии вдоль X
        vertices.push_back(-size * step); vertices.push_back(0.0f); vertices.push_back(i * step);
        vertices.push_back(size * step);  vertices.push_back(0.0f); vertices.push_back(i * step);
    }

    VertexCount = static_cast<int>(vertices.size() / 3);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ObjectShader = std::make_unique<Shader>("vertex.glsl", "grid_fragment.glsl");
}

Grid::~Grid()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Grid::Draw(const glm::mat4& projection, const glm::mat4& view)
{
    ObjectShader->Use();

    GLuint program = ObjectShader->GetProgram();
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 model = glm::mat4(1.0f);
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, VertexCount);
    glBindVertexArray(0);
}
