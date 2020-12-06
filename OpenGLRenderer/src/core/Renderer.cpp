#include "pch.h"
#include "Renderer.h"

std::vector<Scene*> Renderer::s_Scenes;

void Renderer::Init(uint32_t width, uint32_t height)
{
    s_Width = width;
    s_Height = height;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    Renderer::s_Window = glfwCreateWindow(s_Width, s_Height, "OpenGL Playground", NULL, NULL);
    if (Renderer::s_Window == nullptr)
    {
        Shutdown();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(Renderer::s_Window);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    assert(status, "Failed to load glad");
    SetVSync(true);
    spdlog::info("Welcome to spdlog!");

    glfwSetFramebufferSizeCallback(s_Window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    /*std::vector<Scene*> Renderer::s_Scenes;*/

    Scene* testScene = new Scene();
    testScene->AddModel(new Model());
    testScene->Activate();
    s_Scenes.push_back(testScene);
}

void Renderer::Update()
{
    glClearColor((float)196 / 256, (float)196 / 256, (float)196 / 256, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    UpdateActiveScenes();
    processInput(Renderer::s_Window);
    glfwSwapBuffers(Renderer::s_Window);
    glfwPollEvents();
}

void Renderer::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Renderer::SetVSync(bool enabled)
{
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    s_Data.VSync = enabled;
}

bool Renderer::IsVSync()
{
    return s_Data.VSync;
}

void Renderer::Shutdown()
{
    glfwDestroyWindow(s_Window);
    glfwTerminate();

    for (Scene* scene : s_Scenes)
    {
        delete scene;
    }
}

void Renderer::SetScreenSize(uint32_t width, uint32_t height) {
}

void Renderer::UpdateActiveScenes()
{
    for (Scene* scene : s_Scenes)
    {
        if (scene->IsActive())
        {
            scene->Update();
        }
    }
}
