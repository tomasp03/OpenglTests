#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

#define WIN_W 1200
#define WIN_H 1200



static void KeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

GLfloat vertices[] =
{
	-1.0f, 1.0f,
	-1.0f, -1.0f,
	1.0f, 1.0f,
	1.0f, -1.0f
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

	Shader shader("shaders\\basic.vert", "shaders\\basic.frag");
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	VAO1.LinkVBO(VBO1, 0);

	


	int width, height;

	while (!glfwWindowShouldClose(window))
	{
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);



		shader.Activate();

		shader.uni2f("u_screenSize", width, height);
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();
}