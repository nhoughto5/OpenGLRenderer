#pragma once
#include "core/Renderer.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

class Application {
public:
    Application();
    ~Application();

    inline static Application& Get() { return *s_Instance; }
    void Subscribe(IListener* listener);
    void Run();
private:
    using EventCallbackFn = std::function<void(Event&)>;
    void OnEvent(Event& e);
    bool IsVSync();
    void SetVSync(bool enabled);
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);

    struct WindowData
    {
        std::string Title;
        unsigned int Width, Height;
        bool VSync;
        EventCallbackFn EventCallback;
    };

    GLFWwindow* m_Window;
    WindowData m_Data;
    Renderer m_Renderer;
    float m_LastFrameTime = 0.0f;
    std::vector<std::shared_ptr<Scene>> m_Scenes;
    bool m_Running{ false };
    uint32_t m_Width, m_Height;
    bool m_Minimized = false;
    static Application* s_Instance;
    std::vector<IListener*> m_Listeners;
};

