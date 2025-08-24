#include "Objects/BlackHoleLensEffect.h"

BlackHoleLensEffect::BlackHoleLensEffect(BlackHole* blackHole, StarSkybox* skybox, Camera* Cam)
    : BH(blackHole), Skybox(skybox), CameraInstance(Cam)
{
    EventHorizonRadius = BH->GetRadius() + EventHorizonRadius;
    MeshObj = Mesh::CreateCircle(EventHorizonRadius);   
    SetShader("lens_vertex.glsl", "lens_fragment.glsl");
    SetPosition(BH->GetPosition());
}

void BlackHoleLensEffect::Draw(const glm::mat4& projection, const glm::mat4& view)
{
    Skybox->RenderToFramebuffer(projection, view);
    model = CameraInstance->GetBillboardMatrix(Position, model);
    ObjectShader->Use();
    
    // матрицы
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    // экранные размеры
    glUniform2f(glGetUniformLocation(program, "uScreenSize"), Skybox->GetFramebufferWidth(), Skybox->GetFramebufferHeight());

    // центр диска в экранных uv (0..1)
    glm::vec4 centerWorld = glm::vec4(Position.X, Position.Y, Position.Z, 1.0f);
    glm::vec4 centerClip = projection * view * centerWorld;
    glm::vec2 centerNDC = glm::vec2(centerClip) / centerClip.w;     // [-1..1]
    glm::vec2 centerUV = centerNDC * 0.5f + 0.5f;                   // [0..1]
    glUniform2f(glGetUniformLocation(program, "uCenterUV"), centerUV.x, centerUV.y);

    // параметры линзы
    glUniform1f(glGetUniformLocation(program, "uOpacity"), Opacity);
    glUniform1f(glGetUniformLocation(program, "uBlendStrength"), BlendStrength);   
    glUniform1f(glGetUniformLocation(program, "uDistortionK"), Distortion);
    glUniform1f(glGetUniformLocation(program, "uFeather"), Feather);
    glUniform1f(glGetUniformLocation(program, "uDiskRadiusWS"), EventHorizonRadius);
    glUniform1f(glGetUniformLocation(program, "uBHRadiusWS"), BH->GetRadius());

    // текстура фона из FBO
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Skybox->GetFramebufferTexture());
    glUniform1i(glGetUniformLocation(program, "uBackgroundTex"), 0);

    // рисуем диск
    MeshObj->Bind();
    glDrawArrays(GL_TRIANGLES, 0, MeshObj->GetVertexCount());
    MeshObj->Unbind();
}
