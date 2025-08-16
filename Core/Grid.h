#pragma once
#include "SceneObject.h"
#include <vector>

class Grid : public SceneObject
{
public:
    Grid(int size, float step);
    ~Grid();

    void Draw(const glm::mat4& projection, const glm::mat4& view) override;
};
