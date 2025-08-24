#pragma once
#include "Objects/SceneObject.h"
#include "Objects/BlackHole.h"
#include "Objects/StarSkybox.h"
#include "Engine/Camera.h"

class BlackHoleLensEffect : public SceneObject
{
public:
    BlackHoleLensEffect(BlackHole* blackHole, StarSkybox* skybox, Camera* Cam);

    void Draw(const glm::mat4& projection, const glm::mat4& view) override;

private:
    BlackHole* BH;
    StarSkybox* Skybox;
    Camera* CameraInstance;
    float EventHorizonRadius = 5.0f;
    float BlendStrength = 1.f; // 0..1
    float Opacity = 1.0f;
    float Distortion = 0.3f; // сила искажени€
    float Feather = 0.015f; // м€гка€ кромка (в дол€х радиуса)
};
