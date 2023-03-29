#include "Renderer.h"

Renderer::Render::Render(int win_w, int win_h)
	: currentTest(nullptr), testMenu(new test::TestMenu(currentTest))
{
	w_width = win_w;
	w_height = win_h;
	currentTest = testMenu;
	double currentFrame = glfwGetTime();
	double lastFrame = currentFrame;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.WantCaptureMouse = true;
	ImGuiPlatformIO& p_io = ImGui::GetPlatformIO(); (void)p_io;
	ImGui::RenderPlatformWindowsDefault();

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
	io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
	//io.ConfigViewportsNoAutoMerge = true;

	ImGuiWindowClass wclass;
	io.ConfigViewportsNoDefaultParent = true;
	wclass.ViewportFlagsOverrideSet = ImGuiWindowFlags_NoBringToFrontOnFocus;
	wclass.ViewportFlagsOverrideSet = ImGuiViewportFlags_CanHostOtherWindows;


	ImGui::StyleColorsDark();
	Loader::GLFW();
	window = new Window(win_w, win_h, "title");
	Loader::GladGL();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Loader::ImGui(m_window->GetID());
	ImGui_ImplGlfw_InitForOpenGL(window->GetID(), true);
	ImGui_ImplOpenGL3_Init("#version 460");


	testMenu->RegisterTest<test::ClearColor>("Clear color");
	testMenu->RegisterTest<test::Mandelbrot>("Mandelbrot");
	testMenu->RegisterTest<test::Squares>("Squares");
	testMenu->RegisterTest<test::ComputeShader>("ComputeShader");
}


bool Renderer::Render::run()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	if (settings.FullScreen)
	{
		glfwSetWindowMonitor(window->GetID(), glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
		settings.justTrunedOff_FS = true;
	}
	else if (settings.justTrunedOff_FS && !settings.FullScreen)
	{
		glfwSetWindowMonitor(window->GetID(), NULL, mode->width/5, mode->height/5, w_width, w_height, mode->refreshRate);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		settings.justTrunedOff_FS = false;
	}
	glfwSwapInterval(settings.Vsync);
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (currentTest)
	{
		glfwMakeContextCurrent(window->GetID());

		currentTest->OnUpdate(deltaTime);
		currentTest->OnRender(window->GetID());
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Test");
		ImGui::SetWindowFontScale(3.0f);
		if (currentTest != testMenu && ImGui::Button("<-"))
		{
			delete currentTest;
			currentTest = testMenu;
		}
		currentTest->OnImGuiRender();
		ImGui::End();

		ImGui::Begin("Settings");
		ImGui::SetWindowFontScale(3.0f);
		ImGui::Checkbox("Vsync", &settings.Vsync);
		ImGui::Checkbox("FullScreen", &settings.FullScreen);
		ImGui::End();
		ImGui::Render();
		ImGui::EndFrame();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		window->PollEvents();
		window->SwapBuffers();
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	return !glfwWindowShouldClose(window->GetID());
}