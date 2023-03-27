#include "Squares.h"


test::Squares::Squares()
{
	prevTime = 0;
	crntTime = 0;
	counter = 0;
	std::unique_ptr<GLuint[]> indices = std::make_unique<GLuint[]>(NumberOfIndices);
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_shader = new Shader("shaders\\basic.vert", "shaders\\basic.frag");
	m_VAO = new VAO();
	m_VBO = new VBO(nullptr, sizeof(Shapes::Vertex) * NumberOfVertices);
	m_EBO = new EBO(nullptr, sizeof(GLuint) * NumberOfIndices);
	m_VAO->LinkVBO(*m_VBO, 0, 3, sizeof(Shapes::Vertex), offsetof(Shapes::Vertex, Position));
	m_VAO->LinkVBO(*m_VBO, 1, 4, sizeof(Shapes::Vertex), offsetof(Shapes::Vertex, Color));
	m_VAO->Bind();
	m_EBO->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * NumberOfIndices, indices.get(), GL_STATIC_DRAW);

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
	m_VAO->Unbind();
	m_VBO->Unbind();
	m_EBO->Unbind();
}

test::Squares::~Squares()
{
	delete m_shader;
	delete m_VAO;
	delete m_VBO;
	delete m_EBO;
}

void test::Squares::OnUpdate(float deltaTime)
{

	crntTime = glfwGetTime();
	timeDiff = crntTime - prevTime;
	counter++;


	if (timeDiff >= 1.0 / 30.0)
	{
		FPS = std::to_string((1.0 / timeDiff) * counter) + " FPS";
		ms = std::to_string((timeDiff / counter) * 1000);


		prevTime = crntTime;
		counter = 0;
	}

	dt = deltaTime;
	for (int i = 0; i < MaxQuads; i++)
	{
		m_Squares[i].position += m_Squares[i].speed * deltaTime;
		if ((m_Squares[i].position.x + m_Squares[i].size) >= width || m_Squares[i].position.x <= 0)
			m_Squares[i].speed.x *= -1;
		if ((m_Squares[i].position.y + m_Squares[i].size) >= height || m_Squares[i].position.y <= 0)
			m_Squares[i].speed.y *= -1;
	}
}

void test::Squares::OnRender(GLFWwindow* window)
{
	glfwGetFramebufferSize(window, &width, &height);
	float aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);

	auto q0 = Shapes::Quad(m_Squares[0].PosForOpneGL(width, height), m_Squares[0].SizeForOpenGL(width, height), m_Squares[0].color, aspectRatio);
	auto q1 = Shapes::Quad(m_Squares[1].PosForOpneGL(width, height), m_Squares[1].SizeForOpenGL(width, height), m_Squares[1].color, aspectRatio);

	auto vertices = std::make_unique<Shapes::Vertex[]>(NumberOfVertices);
	int quadIterator = 0;
	for (int i = 0; i < MaxQuads; i++)
	{
		auto q = Shapes::Quad(m_Squares[i].PosForOpneGL(width, height), m_Squares[i].SizeForOpenGL(width, height), m_Squares[i].color, aspectRatio);
		memcpy(vertices.get() + quadIterator, q.data(), q.size() * sizeof(Shapes::Vertex));

		quadIterator += q.size();
	}

	m_VBO->Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, NumberOfVertices * sizeof(Shapes::Vertex), vertices.get());


	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_shader->Activate();
	m_VAO->Bind();
	glDrawElements(GL_TRIANGLES, NumberOfIndices, GL_UNSIGNED_INT, 0);
	m_shader->Deactivate();
	m_VAO->Unbind();
	m_VBO->Unbind();
	m_EBO->Unbind();
}

void test::Squares::OnImGuiRender()
{
	ImGui::Text(FPS.c_str());
}
