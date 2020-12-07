#include "pch.h"
#include "Renderer.h"

Renderer::Renderer()
{
}

void Renderer::Init(uint32_t width, uint32_t height)
{
    m_Width = width;
    m_Height = height;

    glEnable(GL_DEPTH_TEST);
}

void Renderer::Update()
{
    glClearColor((float)196 / 256, (float)196 / 256, (float)196 / 256, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_Scene)
    {
        m_Scene->Update();
    }
}

void Renderer::SetCurrentScene(std::shared_ptr<Scene> scene)
{
    m_Scene = scene;
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
    glViewport(0, 0, width, height);
}
