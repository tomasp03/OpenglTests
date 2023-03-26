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
#include "ClearColor.h"

#include "Squares.h"

namespace Renderer
{
	extern class Render
	{
	public:
		Render(int win_w, int win_h);
		bool run();

		test::Squares* scene;

	private:
		double currentFrame;
		double lastFrame;
		double deltaTime;
	};
}
