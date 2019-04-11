#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
class Renderer
{
public:
	Renderer();
	~Renderer();

	void run();
	void OnUpdate();
	void SetVSync(bool enabled);
	bool IsVSync() const;
	void Shutdown();

private:

	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
	};

	WindowData m_Data;
	GLFWwindow* m_Window;
	bool m_Running{ true };
};

