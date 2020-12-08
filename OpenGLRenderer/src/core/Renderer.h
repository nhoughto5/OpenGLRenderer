#pragma once

#include "core/Scene.h"
#include "Core.h"

class Renderer : public IListener
{
public:
    Renderer();
    void Init(uint32_t width, uint32_t height);
    virtual void OnUpdate(TimeStep ts) override;
    virtual void OnEvent(Event& e) override;
    void SetCurrentScene(std::shared_ptr<Scene> scene);
    void OnWindowResize(uint32_t width, uint32_t height);
private:
    std::shared_ptr<Scene> m_Scene;
    uint32_t m_Width, m_Height;
};
