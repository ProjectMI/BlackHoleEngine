#pragma once
#include "Objects/SceneObject.h"
#include <random>

class StarSkybox : public SceneObject
{
public:
    StarSkybox(int starCount, int fbWidth, int fbHeight);
    virtual void Draw(const glm::mat4& projection, const glm::mat4& view) override;

    // ����� �����: ������ � ��������
    void RenderToFramebuffer(const glm::mat4& projection, const glm::mat4& view);
    int GetFramebufferWidth() { return fbWidth; };
    int GetFramebufferHeight() { return fbHeight; };
    GLuint GetFramebufferTexture() const { return colorTex; }

private:
    // ����������
    GLuint framebuffer = 0;
    GLuint colorTex = 0;
    GLuint depthRbo = 0;
    int fbWidth = 0;
    int fbHeight = 0;

    void InitFramebuffer();

private:
    float rotationYaw = 0.0f;      // ������� ����
    float rotationSpeed = 1.0f;    // �������� �������� � ��������/���
    double lastTime = 0.0;         // ����� ����������� �����
};
