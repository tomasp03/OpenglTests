#pragma once
//#include "test.h"
#include "glm/glm.hpp"
#include "glad/glad.h"
#include <imgui.h>
#include "Test.h"

namespace test
{
	class ClearColor : public Test
	{
	public:
		ClearColor();
		~ClearColor();

		void OnUpdate(float deltaTime);
		void OnRender(GLFWwindow* window);
		void OnImGuiRender();

	private:
		glm::vec4 m_Color;
	};
}

