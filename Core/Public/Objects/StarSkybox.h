#pragma once
#include "Objects/SceneObject.h"
#include <random>

class StarSkybox : public SceneObject
{
public:
    StarSkybox(int starCount);
    virtual void Draw(const glm::mat4& projection, const glm::mat4& view) override;
};
