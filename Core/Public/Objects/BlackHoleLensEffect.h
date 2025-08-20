#pragma once
#include "Objects/SceneObject.h"
#include "Objects/BlackHole.h"
#include "Objects/StarSkybox.h"

class BlackHoleLensEffect : public SceneObject
{
public:
    BlackHoleLensEffect(BlackHole* blackHole, StarSkybox* skybox);

    void Draw(const glm::mat4& projection, const glm::mat4& view) override;

private:
    BlackHole* BH;
    StarSkybox* Skybox;
    float EventHorizonRadius = 1.0f;
    float BlendStrength = 0.5f;
    float Opacity = 1.0f;
};
