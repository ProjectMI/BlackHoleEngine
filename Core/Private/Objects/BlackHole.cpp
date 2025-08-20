#include "Objects/BlackHole.h"

BlackHole::BlackHole(float radius) : Radius(radius)
{
    auto vertices = Mesh::CreateUVSphere(radius, 64, 128);
    MeshObj = std::make_unique<Mesh>(vertices);

    SetShader("vertex.glsl", "blackhole_fragment.glsl");
}

void BlackHole::Draw(const glm::mat4& projection, const glm::mat4& view)
{
    ObjectShader->Use();

    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    MeshObj->Bind();
    glDrawArrays(GL_TRIANGLES, 0, MeshObj->GetVertexCount());
    MeshObj->Unbind();
}
