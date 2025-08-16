#include "Objects/SceneObject.h"
#include <glm/gtc/type_ptr.hpp>

void SceneObject::Draw(const glm::mat4& projection, const glm::mat4& view)
{
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    MeshObj->Bind();
    glDrawArrays(GL_LINES, 0, MeshObj->GetVertexCount());
    MeshObj->Unbind();
}

void SceneObject::SetShader(const std::string& vertexPath, const std::string& fragmentPath)
{
    ObjectShader = std::make_unique<Shader>(vertexPath, fragmentPath);
    ObjectShader->Use();
    program = ObjectShader->GetProgram();
    model = glm::mat4(1.0f);
}

