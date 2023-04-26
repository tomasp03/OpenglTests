#include "RayTrace.h"
#include "stb/stb_image_write.h"

static std::string Load(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
}

test::RayTrace::RayTrace()
{
	width = 800;
	height = 800;
	image = new float[width * height * 4];
	bytes = new unsigned char[width * height * 4];

	GLfloat vertices[] =
	{
		-1.0f, 1.0f, 1.0f, 0.0f,
		 1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 0.0f, 0.0f,
		 1.0f,-1.0f, 0.0f, 1.0f
	};

	m_VBO = new VBO(vertices, sizeof(vertices));
	m_VAO = new VAO();
	m_Shader = new Shader("shaders\\RT_shaders\\main.vert", "shaders\\RT_shaders\\main.frag");
	m_VAO->LinkVBO(*m_VBO, 0, 2, 4 * sizeof(GLfloat), 0);
	m_VAO->LinkVBO(*m_VBO, 1, 2, 4 * sizeof(GLfloat), 2);

	m_Spheres = new Sphere[SPHERES_COUNT];
	m_Spheres[1].center = glm::vec3(0.0, 0.0, -5.0);
	m_Spheres[0].center = glm::vec3(0.0, -11.0, -5.0);
	m_Spheres[1].radius = 1.0f;
	m_Spheres[0].radius = 10.0f;

	m_Spheres[1].mat.albido = { 0.1f, 0.2f, 0.8f, 1.0f };
	m_Spheres[0].mat.albido = { 0.8f, 0.2f, 0.1f, 1.0f };

	m_Spheres[1].mat.roughness = 0.2;
	m_Spheres[0].mat.roughness = 0.5;

	m_Spheres[1].mat.emissionColor = m_Spheres[1].mat.albido;
	m_Spheres[1].mat.emissionStrength = 0.5;

	m_Spheres[0].mat.emissionColor = glm::vec4(1);
	m_Spheres[0].mat.emissionStrength = 0.1;

	m_Light = new Sphere();
	m_Light->center = glm::vec3(0, 500, -5);
	m_Light->radius = 600.0f;
	m_Light->mat.albido = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->mat.roughness = 0;
	m_Light->mat.emissionColor = glm::vec4(1);
	m_Light->mat.emissionStrength = 1;

	glActiveTexture(0);
	glCreateTextures(GL_TEXTURE_2D, 1, &screenTex);
	glTextureParameteri(screenTex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(screenTex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(screenTex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(screenTex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


	glTextureStorage2D(screenTex, 1, GL_RGBA, width, height);
	glBindImageTexture(0, screenTex, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA);
}

void test::RayTrace::OnUpdate(float deltaTime)
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

void test::RayTrace::OnRender(GLFWwindow* window)
{
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	m_Shader->Activate();
	glTexImage2D(screenTex, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

	m_Shader->uni2f("u_resolution", width, height);
	m_Shader->uni1f("u_texture", 0);
	//m_Shader->uni4f("u_spheres[0].color", 0.0f, 1.0f, 0.0f, 1.0f);

	for (int i = 0; i < SPHERES_COUNT; i++)
	{
		std::string nameRad = "u_spheres[" + std::to_string(i) + "].radius";
		std::string nameCen = "u_spheres[" + std::to_string(i) + "].center";
		std::string nameCol = "u_spheres[" + std::to_string(i) + "].mat.albido";
		std::string nameRou = "u_spheres[" + std::to_string(i) + "].mat.roughness";
		std::string nameECo = "u_spheres[" + std::to_string(i) + "].mat.emissionColor";
		std::string nameESt = "u_spheres[" + std::to_string(i) + "].mat.emissionStrength";



		m_Shader->uni4f(nameCol.c_str(), m_Spheres[i].mat.albido.x, m_Spheres[i].mat.albido.y, m_Spheres[i].mat.albido.z, m_Spheres[0].mat.albido.w);
		m_Shader->uni3f(nameCen.c_str(), m_Spheres[i].center.x, m_Spheres[i].center.y, m_Spheres[i].center.z);
		m_Shader->uni1f(nameRad.c_str(), m_Spheres[i].radius);
		m_Shader->uni1f(nameRou.c_str(), m_Spheres[i].mat.roughness);
		m_Shader->uni4f(nameECo.c_str(), m_Spheres[i].mat.emissionColor.x, m_Spheres[i].mat.emissionColor.y, m_Spheres[i].mat.emissionColor.z, m_Spheres[i].mat.emissionColor.w);
		m_Shader->uni1f(nameESt.c_str(), m_Spheres[i].mat.emissionStrength);
	}

	m_Shader->uni4f("u_light.color", m_Light->mat.albido.x, m_Light->mat.albido.y, m_Light->mat.albido.z, m_Light->mat.albido.w);
	m_Shader->uni3f("u_light.center", m_Light->center.x, m_Light->center.y, m_Light->center.z);
	m_Shader->uni1f("u_light.radius", m_Light->radius);
	m_Shader->uni1f("u_time", (float)glfwGetTime());
	m_Shader->uni1f("u_show", show);


	m_VAO->Bind();
	glBindTextureUnit(0, screenTex);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
}

void test::RayTrace::OnImGuiRender()
{
	ImGui::Text(FPS.c_str());
	for (int i = 0; i < SPHERES_COUNT; i++)
	{
		std::string name = "sphere " + std::to_string(i);
		ImGui::ColorEdit4(name.c_str(), &m_Spheres[i].mat.albido.x);
		ImGui::SliderFloat(name.c_str(), &m_Spheres[i].mat.roughness, 0.0f, 1.0f);
	}
	ImGui::Text("Light");
	ImGui::SliderFloat3("Position", &m_Light->center.x, -10000.f, 10000.f);
	ImGui::SliderFloat("show", &show, 0.f, 1.f);
	ImGui::SliderFloat("read", &read, 0.f, 1.f);



	if (ImGui::Button("save"))
	{
		stbi_write_png("testCompute.png", width, height, 4, bytes, 4 * width);
	}
}
