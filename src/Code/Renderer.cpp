#include "Renderer.h"

Renderer::Render::Render(int win_w, int win_h)
{
	const unsigned int MaxQuads = 10000;
	const unsigned int NuberOfVertices = 4 * MaxQuads;
	const unsigned int NumberOfIndices = 6 * MaxQuads;
	GLuint indices[NumberOfIndices];

	unsigned int offset = 0;
	for (int i = 0; i < NumberOfIndices; i += 6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 1 + offset;
		
		offset += 4;
	}


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGuiPlatformIO& p_io = ImGui::GetPlatformIO(); (void)p_io;
	//ImGui::RenderPlatformWindowsDefault();

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;
	io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;


	ImGui::StyleColorsDark();
	Loader::GLFW();
	m_window = new Window(1200, 1200, "title");
	Loader::GladGL();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Loader::ImGui(m_window->GetID());
	ImGui_ImplGlfw_InitForOpenGL(m_window->GetID(), true);
	ImGui_ImplOpenGL3_Init("#version 460");


	m_shader = new Shader("shaders\\basic.vert", "shaders\\basic.frag");
	m_VAO = new VAO();
	m_VBO = new VBO(nullptr, sizeof(Shapes::Vertex) * NuberOfVertices);
	m_EBO = new EBO(nullptr, sizeof(GLuint) * NumberOfIndices);
	m_VAO->LinkVBO(*m_VBO, 0, 3, sizeof(Shapes::Vertex), offsetof(Shapes::Vertex, Position));
	m_VAO->LinkVBO(*m_VBO, 1, 4, sizeof(Shapes::Vertex), offsetof(Shapes::Vertex, Color));
	m_VAO->Bind();
	m_EBO->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glfwSwapInterval(1);


}


bool Renderer::Render::run()
{
	glfwMakeContextCurrent(m_window->GetID());

	int width, height;
	glfwGetFramebufferSize(m_window->GetID(), &width, &height);
	float aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);

	auto q0 = Shapes::Quad(m_data.position0, 0.5f, m_data.color0, aspectRatio);
	auto q1 = Shapes::Quad(m_data.position1, 0.25f, m_data.color1, aspectRatio);

	Shapes::Vertex vertices[8];
	memcpy(vertices, q0.data(), q0.size() * sizeof(Shapes::Vertex));
	memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Shapes::Vertex));



	m_VBO->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);


	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	m_shader->Activate();

	// Bind the VAO so OpenGL knows to use it
	m_VAO->Bind();
	m_shader->uni1f("u_scale", m_data.scale);
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("1");
	ImGui::SetWindowFontScale(3.0f);
	ImGui::SliderFloat("Position X", &m_data.position1.x, -1.0f, 1.0f);
	ImGui::SliderFloat("Position Y", &m_data.position1.y, -1.0f, 1.0f);
	ImGui::ColorEdit4("color", &m_data.color1.x);
	ImGui::End();



	ImGui::Begin("Q1");
	ImGui::SetWindowFontScale(3.0f);
	ImGui::SliderFloat("Position X", &m_data.position0.x, -1.0f, 1.0f);
	ImGui::SliderFloat("Position Y", &m_data.position0.y, -1.0f, 1.0f);
	ImGui::ColorEdit4("color", &m_data.color0.x);
	ImGui::End();


	ImGui::Render();
	ImGui::EndFrame();


	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	GLFWwindow* backup_current_context = glfwGetCurrentContext();
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	glfwMakeContextCurrent(backup_current_context);
	m_window->PollEvents();
	m_window->SwapBuffers();

	return !glfwWindowShouldClose(m_window->GetID());
}