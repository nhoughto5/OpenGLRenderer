#include "pch.h"
#include <glad/glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>

int main(void)
{
	const int HEIGHT = 600;
	const int WIDTH = 800;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, WIDTH, HEIGHT);
	while (true);
}