#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIN_W 1200
#define WIN_H 1200



static void KeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

float vertices[] =
{
	0.0, 0.5,
	0.5, -0.5,
	-0.5, -0.5
};

int main()
{
	if (!glfwInit())
	{
		std::cout << "Error: Failed to initialize GLFW!" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, "My window", NULL, NULL);
	if (!window)
	{
		std::cout << "Error: Failed to create window!" << std::endl;
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyPressed);

	if (!gladLoadGL())
	{
		std::cout << "Error: Failed to load glad!" << std::endl;
		glfwTerminate();
		return -3;
	}

	

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
}