#include "Objects/StarSkybox.h"

StarSkybox::StarSkybox(int starCount)
{
    std::vector<Vector3D> stars;
    stars.reserve(starCount);

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    for (int i = 0; i < starCount; ++i)
    {
        glm::vec3 v;
        do {
            v = glm::vec3(dist(rng), dist(rng), dist(rng));
        } while (glm::length(v) < 0.01f);
        v = glm::normalize(v);
        stars.emplace_back(v.x, v.y, v.z);
    }

    MeshObj = std::make_unique<Mesh>(stars);
    glEnable(GL_PROGRAM_POINT_SIZE);
    SetShader("stars_vertex.glsl", "stars_fragment.glsl");
}

void StarSkybox::Draw(const glm::mat4& projection, const glm::mat4& view)
{
    ObjectShader->Use();
    glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view));
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(viewNoTranslation));
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

    MeshObj->Bind();
    glDrawArrays(GL_POINTS, 0, MeshObj->GetVertexCount());
    MeshObj->Unbind();
}
