#include "pch.h"
#include "Renderer.h"
#include "Application.h"

Renderer::Renderer() :
    m_Width(INIT_WIDTH),
    m_Height(INIT_HEIGHT)
{
}

void Renderer::Init(uint32_t width, uint32_t height)
{
    m_Width = width;
    m_Height = height;
    InitServices();
    Application::Get().Subscribe(this);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::OnUpdate(TimeStep ts) {
    glClearColor((float)222 / 256, (float)235 / 256, (float)255 / 256, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_Scene) {
        m_Scene->Update();
    }
}

void Renderer::OnEvent(Event& e) {
}

void Renderer::SetCurrentScene(std::shared_ptr<Scene> scene)
{
    m_Scene = scene;
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
    glViewport(0, 0, width, height);
}

void Renderer::InitServices() {
    LightService::GetInstance();
}
