#include "Objects/SceneObject.h"

void SceneObject::SetShader(const std::string& vertexPath, const std::string& fragmentPath)
{
    ObjectShader = std::make_unique<Shader>(vertexPath, fragmentPath);
    ObjectShader->Use();
    program = ObjectShader->GetProgram();
    model = glm::mat4(1.0f);
}

void SceneObject::UpdateModel()
{
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(Position.X, Position.Y, Position.Z));
    model = glm::rotate(model, glm::radians(Rotation.Pitch), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(Rotation.Yaw), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(Rotation.Roll), glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(Scale.X, Scale.Y, Scale.Z));
}
