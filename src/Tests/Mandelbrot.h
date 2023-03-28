#pragma once
#include <string>
#include "Test.h"
#include <vector>
#include "VAO.h"
#include "VBO.h"
#include "Shader.h"

namespace test
{
	class Mandelbrot : public Test
	{
	private:
		VAO* m_VAO;
		VBO* m_VBO;
		
		Shader* currentShader;
		std::vector<std::pair<std::string, Shader*>> shaders;

		float crntTime = 0;
		float prevTime = 0;
		float timeDiff = 0;
		int counter = 0;

		std::string FPS = " ";
		std::string ms = " ";

		double mouse_x = 0;
		double mouse_y = 0;



	public:
		Mandelbrot();

		void OnRender(GLFWwindow* window);
		void OnImGuiRender();
		void OnUpdate(float deltaTime);

	};
}

