#include "Renderer.h"

Renderer::Render::Render(int win_w, int win_h)
{


	Loader::GLFW();
	m_window = new Window(1200, 1200, "title");
	Loader::GladGL();
	Loader::ImGui(m_window->GetID());

	m_shader = new Shader("shaders\\basic.vert", "shaders\\basic.frag");
	m_VAO = new VAO();
	m_VBO = new VBO(nullptr, sizeof(Shapes::Vertex) * 1000);
	m_EBO = new EBO(nullptr, sizeof(GLuint) * 1000);
	m_VAO->LinkVBO(*m_VBO, 0, 3, sizeof(Shapes::Vertex), offsetof(Shapes::Vertex, Position));

	glfwSwapInterval(1);
}


bool Renderer::Render::run()
{
	int width, height;
	glfwGetFramebufferSize(m_window->GetID(), &width, &height);
	glViewport(0, 0, width, height);

	auto q0 = Shapes::Quad(m_data.position0, 0.5f);
	auto q1 = Shapes::Quad(m_data.position1, 0.25f);

	Shapes::Vertex vertices[8];
	memcpy(vertices, q0.data(), q0.size() * sizeof(Shapes::Vertex));
	memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Shapes::Vertex));

	GLuint indices[] =
	{
		0, 1, 2, 2, 3, 1,
		4, 5, 6, 6, 7, 5
	};

	m_VBO->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	m_EBO->Bind();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// ImGUI window creation
	ImGui::Begin("Quads");
	ImGui::SetWindowFontScale(3.0f);
	// Text that appears in the window
	ImGui::Text("Hello there adventurer!");

	ImGui::SliderFloat("Position X", &m_data.position0.x, -1.0f, 1.0f);
	ImGui::SliderFloat("Position Y", &m_data.position0.y, -1.0f, 1.0f);


	ImGui::End();

	m_shader->Activate();

	// Bind the VAO so OpenGL knows to use it
	m_VAO->Bind();
	m_shader->uni1f("u_scale", m_data.scale);
	m_shader->uni4f("u_color", m_data.color[0], m_data.color[1], m_data.color[2], m_data.color[3]);
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);


	// Renders the ImGUI elements
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// Swap the back buffer with the front buffer
	m_window->SwapBuffers();
	// Take care of all GLFW events
	m_window->PollEvents();

	return !glfwWindowShouldClose(m_window->GetID());
}