#include "Objects/StarSkybox.h"
#include "Engine/Engine.h"

StarSkybox::StarSkybox(int starCount, int fbWidth, int fbHeight)
    : fbWidth(fbWidth), fbHeight(fbHeight)
{
    std::vector<Vector3D> stars;
    stars.reserve(starCount);

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    for (int i = 0; i < starCount; ++i)
    {
        glm::vec3 v;
        do {
            v = glm::vec3(dist(rng), dist(rng), dist(rng));
        } while (glm::length(v) < 0.01f);
        v = glm::normalize(v);
        stars.emplace_back(v.x, v.y, v.z);
    }

    MeshObj = std::make_unique<Mesh>(stars);
    glEnable(GL_PROGRAM_POINT_SIZE);
    SetShader("stars_vertex.glsl", "stars_fragment.glsl");

    InitFramebuffer();
}

void StarSkybox::InitFramebuffer()
{
    // создаём FBO
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // цветовой текстурный аттачмент
    glGenTextures(1, &colorTex);
    glBindTexture(GL_TEXTURE_2D, colorTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fbWidth, fbHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTex, 0);

    // depth renderbuffer
    glGenRenderbuffers(1, &depthRbo);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, fbWidth, fbHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("StarSkybox FBO is not complete!");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void StarSkybox::RenderToFramebuffer(const glm::mat4& projection, const glm::mat4& view)
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, fbWidth, fbHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Draw(projection, view);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void StarSkybox::Draw(const glm::mat4& projection, const glm::mat4& view)
{
    glDepthMask(GL_FALSE);

    // обновляем угол (кадровая независимость через Engine::fps)
    if (Engine::fps > 0.0) {
        rotationYaw += rotationSpeed / static_cast<float>(Engine::fps);
        if (rotationYaw > 360.0f) rotationYaw -= 360.0f;
    }

    ObjectShader->Use();
    glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view));

    // матрица вращения вокруг Y
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(rotationYaw), glm::vec3(0.0f, 1.0f, 0.0f));

    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(viewNoTranslation));
    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    MeshObj->Bind();
    glDrawArrays(GL_POINTS, 0, MeshObj->GetVertexCount());
    MeshObj->Unbind();

    glDepthMask(GL_TRUE);
}

