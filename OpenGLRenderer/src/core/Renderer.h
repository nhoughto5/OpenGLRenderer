#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "core/Shader.h"
#include "core/Model.h"
#include <core\Scene.h>

class Renderer
{
public:

	static void Init(uint32_t width, uint32_t height);
	static void Update();
	static void processInput(GLFWwindow* window);
	static void SetVSync(bool enabled);
	static bool IsVSync();
	static void Shutdown();
	static void SetScreenSize(uint32_t width, uint32_t height);

private:
	static void UpdateActiveScenes();

	static std::vector<Scene*> s_Scenes;

	static inline uint32_t s_Width, s_Height;
	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
	};

	static inline WindowData s_Data;
	static inline GLFWwindow* s_Window;
	static inline bool s_Running{ false };
};

