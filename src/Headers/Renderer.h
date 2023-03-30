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
#include "Mandelbrot.h"
#include "ComputeShader.h"
#include "stb/stb_image.h"

namespace Renderer
{
	struct Settings
	{
		bool Vsync = true;
		bool FullScreen = false;
		bool justTrunedOff_FS = false;
	};
	extern class Render
	{
	public:
		Render(int win_w, int win_h);
		bool run();

		test::Test* currentTest;
		test::TestMenu* testMenu;

		Window* window;
		Settings settings;
		int w_width = 0;
		int w_height = 0;

	private:
		double currentFrame;
		double lastFrame;
		double deltaTime;
	};
}
