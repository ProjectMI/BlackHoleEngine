#pragma once
#include "Objects/SceneObject.h"
#include "Objects/BlackHole.h"


class Grid : public SceneObject
{
public:
    Grid(int size, float step, BlackHole* blackHole, float maxDepth);
    virtual void Draw(const glm::mat4& projection, const glm::mat4& view) override;
private:
    float ComputeDeformation(float x, float z, float maxDepth);
    std::vector<Vector3D> GenerateTriangles(const std::vector<Vector3D>& vertices, int dim);

    BlackHole* BH = nullptr;
};

