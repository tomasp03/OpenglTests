#include "Mandelbrot.h"

namespace test
{
	Mandelbrot::Mandelbrot()
		: m_VAO(new VAO())
	{
		GLfloat m_vertices[8] = 
		{
			-1.0f, 1.0f,
			 1.0f, 1.0f,
			-1.0f,-1.0f,
			 1.0f,-1.0f
		};
		m_VBO = new VBO(m_vertices, sizeof(m_vertices));

		shaders.push_back(std::pair<std::string, Shader*>("Mandelbrot", new Shader("shaders\\Mandelbrot.vert", "shaders\\Mandelbrot.frag")));
		shaders.push_back(std::pair<std::string, Shader*>("Forrest", new Shader("shaders\\Mandelbrot.vert", "shaders\\Forrest.frag")));
		shaders.push_back(std::pair<std::string, Shader*>("Water", new Shader("shaders\\Mandelbrot.vert", "shaders\\water.frag")));
		shaders.push_back(std::pair<std::string, Shader*>("Terrain", new Shader("shaders\\Mandelbrot.vert", "shaders\\Terrain.frag")));

		currentShader = shaders[0].second;

		m_VAO->LinkVBO(*m_VBO, 0, 2, 2 * sizeof(GLfloat), 0);
	}

	void Mandelbrot::OnRender(GLFWwindow* window)
	{
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwGetCursorPos(window, &mouse_x, &mouse_y);

		currentShader->Activate();
		currentShader->uni1f("u_Time", glfwGetTime());
		currentShader->uni2f("u_resolution", width, height);
		currentShader->uni2f("u_Mouse", (float)mouse_x, (float)mouse_y);
		m_VAO->Bind();
		//m_VBO->Bind();
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	void Mandelbrot::OnImGuiRender()
	{
		ImGui::Text(FPS.c_str());
		for (auto& pair : shaders)
		{
			if (ImGui::Button(pair.first.c_str()))
			{
				currentShader = pair.second;
			}
		}
	}

	void Mandelbrot::OnUpdate(float deltaTime)
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
	}
}