#include "Objects/BlackHoleLensEffect.h"

BlackHoleLensEffect::BlackHoleLensEffect(BlackHole* blackHole, StarSkybox* skybox)
    : BH(blackHole), Skybox(skybox)
{
    EventHorizonRadius = BH->GetRadius() + EventHorizonRadius;
    SetPosition(BH->GetPosition());
    SetShader("lens_vertex.glsl", "lens_fragment.glsl");
}

void BlackHoleLensEffect::Draw(const glm::mat4& projection, const glm::mat4& view)
{
    Skybox->RenderToFramebuffer(projection, view);
    ObjectShader->Use();
}
