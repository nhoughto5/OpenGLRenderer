#include "pch.h"
#include "Application.h"
#include "core/Renderer.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

Application* Application::s_Instance = nullptr;

Application::Application() :
    m_Width(INIT_WIDTH),
    m_Height(INIT_HEIGHT) {
    OGLR_CORE_ASSERT(!s_Instance, "Multiple application instances");
    s_Instance = this;

    m_Data.Title = "OGLR";
    m_Data.Width = m_Width;
    m_Data.Height = m_Height;
    m_Data.VSync = false;
    m_Data.EventCallback = OGLR_BIND_EVENT_FN(Application::OnEvent);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Data.Title.c_str(), NULL, NULL);
    if (m_Window == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);

    glfwSetWindowUserPointer(m_Window, &m_Data);

    glfwMakeContextCurrent(m_Window);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    assert(status, "Failed to load glad");
    SetVSync(true);

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

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
        auto& data = *((WindowData*)glfwGetWindowUserPointer(window));

        KeyTypedEvent event((int)keycode);
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
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

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action) {
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

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event);
    });
}

Application::~Application() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Application::Subscribe(IListener* listener) {
    m_Listeners.push_back(listener);
}

void Application::Run() {
    Log::Init();

    pugi::xml_document config;
    pugi::xml_parse_result result = config.load_file(MASTER_CONFIG.c_str());
    OGLR_ASSERT(result.status == 0, "FAILED TO MASTER CONFIG");

    std::shared_ptr<Scene> testScene;
    for (const auto& app : config.children()) {
        for (const auto& child : app.children()) {
            std::string childName = child.name();
            if (childName.compare(SCENE) == 0) {
                testScene = std::make_shared<Scene>(SCENE_FOLDER + child.first_child().value());
                testScene->Activate();
                m_Scenes.push_back(testScene);
            }
        }
    }

    m_Renderer.Init(m_Width, m_Height);
    m_Running = true;
    m_Renderer.SetCurrentScene(testScene);
    while (m_Running) {
        float time = (float)glfwGetTime();
        TimeStep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;
        if (!m_Minimized) {
            glfwSwapBuffers(m_Window);
            glfwPollEvents();

            for (auto it = m_Listeners.end(); it != m_Listeners.begin(); ) {
                (*--it)->OnUpdate(timestep);
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack) {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End(m_Width, m_Height);
        }
    }
}

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(OGLR_BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(OGLR_BIND_EVENT_FN(Application::OnWindowResize));
    for (auto it = m_Listeners.end(); it != m_Listeners.begin(); ) {
        (*--it)->OnEvent(e);
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

bool Application::IsVSync() {
    return m_Data.VSync;
}

void Application::SetVSync(bool enabled) {
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_Data.VSync = enabled;
}

void Application::PushLayer(Layer* layer) {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach(m_Window);
}

void Application::PushOverlay(Layer* layer) {
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach(m_Window);
}