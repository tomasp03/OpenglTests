#pragma once
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <glm/glm.hpp>

#include "Loader.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Window.h"
#include "Shapes.h"

namespace Renderer
{
	struct Data
	{
		float scale = 1.0f;
		glm::vec4 color0 = glm::vec4(1.0f);
		glm::vec4 color1 = glm::vec4(1.0f);
		glm::vec2 position0 = { -0.9f, 0.9f };
		glm::vec2 position1 = {  0.0f, 0.0f };
	};

	extern class Render
	{
	public:
		Window* m_window;
		Shader* m_shader;
		VBO* m_VBO;
		VAO* m_VAO;
		EBO* m_EBO;

		Data m_data;


	public:
		Render(int win_w, int win_h);
		bool run();
	};

}
