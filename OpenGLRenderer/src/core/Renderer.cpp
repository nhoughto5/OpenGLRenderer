#include "pch.h"
#include "Renderer.h"

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

	Shader test("/shaders/triangle.glsl");
	test.Bind();
}

void Renderer::Update()
{
	glClearColor((float)196 / 256, (float)196 / 256, (float)196 / 256, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwPollEvents();
	glfwSwapBuffers(Renderer::s_Window);
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
}

void Renderer::SetScreenSize(uint32_t width, uint32_t height) {
}
