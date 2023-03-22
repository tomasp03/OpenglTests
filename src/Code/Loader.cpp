#include "Loader.h"

void Loader::Init()
{
	GLFW();
	GladGL();
}

void Loader::GLFW()
{
	if (!glfwInit())
	{
		std::cout << "Error: Failed to initialize GLFW!" << std::endl;
		glfwTerminate();
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Loader::GladGL()
{
	if (!gladLoadGL())
	{
		std::cout << "Error: Failed to load glad!" << std::endl;
		glfwTerminate();
		return;
	}
}

void Loader::ImGui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}
