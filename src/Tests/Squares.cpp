#include "Squares.h"
#include <string>
#include <iostream>

test::Squares::Squares(int w_width, int w_height)
{
	prevTime = 0;
	crntTime = 0;
	counter = 0;
	GLuint* indices = new GLuint[NumberOfIndices];
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
	m_window = new Window(w_width, w_height, "title");
	Loader::GladGL();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Loader::ImGui(m_window->GetID());
	ImGui_ImplGlfw_InitForOpenGL(m_window->GetID(), true);
	ImGui_ImplOpenGL3_Init("#version 460");


	m_shader = new Shader("shaders\\basic.vert", "shaders\\basic.frag");
	m_VAO = new VAO();
	m_VBO = new VBO(nullptr, sizeof(Shapes::Vertex) * NumberOfVertices);
	m_EBO = new EBO(nullptr, sizeof(GLuint) * NumberOfIndices);
	m_VAO->LinkVBO(*m_VBO, 0, 3, sizeof(Shapes::Vertex), offsetof(Shapes::Vertex, Position));
	m_VAO->LinkVBO(*m_VBO, 1, 4, sizeof(Shapes::Vertex), offsetof(Shapes::Vertex, Color));
	m_VAO->Bind();
	m_EBO->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * NumberOfIndices, indices, GL_STATIC_DRAW);

	glfwSwapInterval(0);

	delete[] indices;
	for (int i = 0; i < MaxQuads; i++)
	{
		float x = rand() % 1000 + 200;
		float y = rand() % 1000 + 200;

		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);;
		float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);;
		float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);;

		m_Squares[i].speed = { x, y };
		m_Squares[i].color = { r, g, b, 1 };
	}
}

test::Squares::~Squares()
{
	delete m_window;
	delete m_shader;
	delete m_VAO;
	delete m_VBO;
	delete m_EBO;
}

void test::Squares::OnUpdate(float deltaTime)
{
	dt = deltaTime;
	int width, height;
	glfwGetFramebufferSize(m_window->GetID(), &width, &height);
	for (int i = 0; i < MaxQuads; i++)
	{
		m_Squares[i].position += m_Squares[i].speed * deltaTime;
		if ((m_Squares[i].position.x + m_Squares[i].size) >= width || m_Squares[i].position.x <= 0)
			m_Squares[i].speed.x *= -1;
		if ((m_Squares[i].position.y + m_Squares[i].size) >= height || m_Squares[i].position.y <= 0)
			m_Squares[i].speed.y *= -1;
	}
}

void test::Squares::OnRender()
{
	glfwMakeContextCurrent(m_window->GetID());

	int width, height;
	glfwGetFramebufferSize(m_window->GetID(), &width, &height);
	float aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);

	auto q0 = Shapes::Quad(m_Squares[0].PosForOpneGL(width, height), m_Squares[0].SizeForOpenGL(width, height), m_Squares[0].color, aspectRatio);
	auto q1 = Shapes::Quad(m_Squares[1].PosForOpneGL(width, height), m_Squares[1].SizeForOpenGL(width, height), m_Squares[1].color, aspectRatio);

	Shapes::Vertex* vertices = new Shapes::Vertex[NumberOfVertices];
	int quadIterator = 0;
	for (int i = 0; i < MaxQuads; i++)
	{
		auto q = Shapes::Quad(m_Squares[i].PosForOpneGL(width, height), m_Squares[i].SizeForOpenGL(width, height), m_Squares[i].color, aspectRatio);
		memcpy(vertices + quadIterator, q.data(), q.size() * sizeof(Shapes::Vertex));

		quadIterator += q.size();
	}

	m_VBO->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, NumberOfVertices * sizeof(Shapes::Vertex), vertices);

	delete[] vertices;

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_shader->Activate();
	m_VAO->Bind();
	glDrawElements(GL_TRIANGLES, NumberOfIndices, GL_UNSIGNED_INT, 0);

	m_window->PollEvents();
	m_window->SwapBuffers();
}

void test::Squares::OnImGuiRender()
{
	crntTime = glfwGetTime();
	timeDiff = crntTime - prevTime;
	counter++;


	if (timeDiff >= 15.0 / 30.0)
	{
		FPS = std::to_string((1.0 / timeDiff) * counter) + " FPS";
		ms = std::to_string((timeDiff / counter) * 1000);

		prevTime = crntTime;
		counter = 0;
	}

	int width, height;
	glfwGetFramebufferSize(m_window->GetID(), &width, &height);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();

	ImGui::Begin("QUAD 1");
	ImGui::Text(FPS.c_str());

	ImGui::SetWindowFontScale(3.0f);
	ImGui::End();
	ImGui::Render();
	ImGui::EndFrame();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	GLFWwindow* backup_current_context = glfwGetCurrentContext();
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	glfwMakeContextCurrent(backup_current_context);
}

GLFWwindow* test::Squares::WindowID()
{
	return m_window->GetID();
}
