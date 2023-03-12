#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIN_W 1200
#define WIN_H 1200

int main()
{
	if (!glfwInit())
	{
		std::cout << "Error: Failed to initialize GLFW!" << std::endl;
		glfwTerminate();
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(WIN_W, WIN_H, "My window", NULL, NULL);

	

	glfwTerminate();
}