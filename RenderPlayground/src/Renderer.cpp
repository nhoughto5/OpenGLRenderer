#include "pch.h"
#include "Renderer.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{

}

void Renderer::run()
{
	const int HEIGHT = 768;
	const int WIDTH = 1024;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	m_Window = glfwCreateWindow(WIDTH, HEIGHT, "EA Render Playground", NULL, NULL);
	if (m_Window == nullptr)
	{
		Shutdown();
		throw std::runtime_error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(m_Window);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	assert(status, "Failed to load glad");
	SetVSync(true);

	while (m_Running) {
		glClearColor((float)196/256, (float)196/256, (float)196/256, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		OnUpdate();
	}
}

void Renderer::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Renderer::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_Data.VSync = enabled;
}

bool Renderer::IsVSync() const
{
	return m_Data.VSync;
}

void Renderer::Shutdown()
{
	glfwDestroyWindow(m_Window);
}