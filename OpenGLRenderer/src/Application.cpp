#include "pch.h"
#include "Application.h"
#include "core/Renderer.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
Application* Application::s_Instance = nullptr;

Application::Application() :
    m_Width(1024),
    m_Height(768)
{
    OGLR_CORE_ASSERT(!s_Instance, "Multiple application instances");
    s_Instance = this;

    m_Data.Title = "OGLR";
    m_Data.Width = m_Width;
    m_Data.Height = m_Height;
    m_Data.VSync = false;
    m_Data.EventCallback = BIND_EVENT_FN(Application::OnEvent);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    m_Window = glfwCreateWindow(m_Width, m_Height, "OpenGL Playground", NULL, NULL);
    if (m_Window == nullptr)
    {
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwSetWindowUserPointer(m_Window, &m_Data);

    glfwMakeContextCurrent(m_Window);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    assert(status, "Failed to load glad");
    SetVSync(true);
    spdlog::info("Welcome to spdlog!");

    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    // SetUp Events
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
    });

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
    {
        auto& data = *((WindowData*)glfwGetWindowUserPointer(window));

        KeyTypedEvent event((int)keycode);
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, 1);
                data.EventCallback(event);
                break;
            }
        }
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action)
        {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
        }
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event);
    });
}

Application::~Application()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Application::Subscribe(IListener& listener)
{
    m_Listeners.push_back(listener);
}

void Application::Run() {
    Log::Init();

    std::shared_ptr<Scene> testScene(new Scene(SCENE_FOLDER + "triangle.xml"));
    testScene->Activate();
    m_Scenes.push_back(testScene);

    m_Renderer.Init(m_Width, m_Height);
    m_Running = true;
    m_Renderer.SetCurrentScene(testScene);
    while (m_Running) {
        m_Renderer.Update();
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Application::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
    for (auto it = m_Listeners.end(); it != m_Listeners.begin(); ) {
        (*--it).OnEvent(e);
        if (e.Handled) break;
    }
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
    m_Running = false;
    return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e) {
    if (e.GetWidth() == 0 || e.GetHeight() == 0) {
        m_Minimized = true;
        return false;
    }

    m_Minimized = false;
    m_Renderer.OnWindowResize(e.GetWidth(), e.GetHeight());
    return false;
}

bool Application::IsVSync()
{
    return m_Data.VSync;
}

void Application::SetVSync(bool enabled)
{
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_Data.VSync = enabled;
}

