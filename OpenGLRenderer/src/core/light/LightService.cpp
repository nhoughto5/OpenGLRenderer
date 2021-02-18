#include "pch.h"
#include "LightService.h"
#include "Application.h"

LightService* LightService::s_Instance = 0;

LightService* LightService::GetInstance() {
    if (!s_Instance) {
        s_Instance = new LightService();
    }
    return s_Instance;
}

Light LightService::GetAmbientLight() {
    return m_AmbienLight;
}

std::vector<std::shared_ptr<Light>>& LightService::GetLights() {
    return m_Lights;
}

void LightService::SetAmbientLight(glm::vec3 color, float strength) {
    m_AmbienLight.color = color;
    m_AmbienLight.strength = strength;
}

void LightService::AddLight(std::shared_ptr<Light> light) {
    m_Lights.push_back(light);
}

void LightService::CreateShadowmaps()
{
    for (const auto light : m_Lights)
    {
        glGenFramebuffers(1, &light->depthMapFBO);
        glGenTextures(1, &light->depthMapTexture);
        glBindTexture(GL_TEXTURE_2D, light->depthMapTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
            light->shadowMapWidth, light->shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glBindFramebuffer(GL_FRAMEBUFFER, light->depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, light->depthMapTexture, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    m_ShadowShader.SetShaderFileName("shadow.glsl");
}

void LightService::StartShadowRender()
{
    m_ShadowShader.Bind();
    for (const auto light : m_Lights)
    {
        glViewport(0, 0, light->shadowMapWidth, light->shadowMapHeight);
        glBindFramebuffer(GL_FRAMEBUFFER, light->depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
    }
}

void LightService::EndShadowRender()
{
    for (const auto light : m_Lights)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, Application::Get().GetWidth(), Application::Get().GetHeight());
    }

    m_ShadowShader.Unbind();
}

void LightService::SetShadowModelMatrix(glm::mat4 modelMat)
{
    if(m_ShadowShader.isLoaded())
    {
        m_ShadowShader.UploadUniformMat4("u_Model", modelMat);
    }
}

void LightService::SetShadowLightTransport(glm::mat4 lightTransport)
{
    if (m_ShadowShader.isLoaded())
    {
        m_ShadowShader.UploadUniformMat4("u_LightSpaceMatrix", lightTransport);
    }
}
