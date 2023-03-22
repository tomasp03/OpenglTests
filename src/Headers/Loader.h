#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

namespace Loader
{
	extern void Init();
	extern void GLFW();
	extern void GladGL();
	extern void ImGui(GLFWwindow* window);
}
