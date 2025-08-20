#pragma once
#include "Objects/SceneObject.h"

class BlackHole : public SceneObject
{
public:
    BlackHole(float radius);
    virtual void Draw(const glm::mat4& projection, const glm::mat4& view) override;
    float GetRadius() { return Radius; };
private:
    float Radius;
};
