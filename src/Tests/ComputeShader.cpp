
#include "ComputeShader.h"

test::ComputeShader::ComputeShader()
{
	stbi_flip_vertically_on_write(true);
	int imageSize = s_widht * s_height * 4;
	bytes = new unsigned char[imageSize];
	GLfloat vertices[] =
	{
		-1.0f, -1.0f , 0.0f, 0.0f, 0.0f,
		-1.0f,  1.0f , 0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f , 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f , 0.0f, 1.0f, 0.0f,
	};

	GLuint indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};

	const char* screenVertexShaderSource = R"(#version 460 core
	layout (location = 0) in vec3 pos;
	layout (location = 1) in vec2 uvs;
	out vec2 UVs;
	void main()
	{
		gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
		UVs = uvs;
	})";
	const char* screenFragmentShaderSource = R"(#version 460 core
	out vec4 FragColor;
	uniform sampler2D screen;
	in vec2 UVs;
	void main()
	{
		FragColor = texture(screen, UVs);
	})";

	std::string cs = Load("shaders\\Basic.comp");
	const char* ComputeSource = cs.c_str();

	GLuint VBO, EBO;
	glCreateVertexArrays(1, &VAO);
	glCreateBuffers(1, &VBO);
	glCreateBuffers(1, &EBO);

	glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glNamedBufferData(EBO, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(VAO, 0);
	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

	glEnableVertexArrayAttrib(VAO, 1);
	glVertexArrayAttribBinding(VAO, 1, 0);
	glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));

	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 5 * sizeof(GLfloat));
	glVertexArrayElementBuffer(VAO, EBO);


	glCreateTextures(GL_TEXTURE_2D, 1, &screenTex);
	glTextureParameteri(screenTex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(screenTex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(screenTex, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(screenTex, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureStorage2D(screenTex, 1, GL_RGBA32F, s_widht, s_height);
	glBindImageTexture(0, screenTex, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

	screenVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(screenVertexShader, 1, &screenVertexShaderSource, NULL);
	glCompileShader(screenVertexShader);
	screenFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(screenFragmentShader, 1, &screenFragmentShaderSource, NULL);
	glCompileShader(screenFragmentShader);

	screenShaderProgram = glCreateProgram();
	glAttachShader(screenShaderProgram, screenVertexShader);
	glAttachShader(screenShaderProgram, screenFragmentShader);
	glLinkProgram(screenShaderProgram);

	glDeleteShader(screenVertexShader);
	glDeleteShader(screenFragmentShader);


	computeShader = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(computeShader, 1, &ComputeSource, NULL);
	glCompileShader(computeShader);

	computeProgram = glCreateProgram();
	glAttachShader(computeProgram, computeShader);
	glLinkProgram(computeProgram);


	int work_grp_cnt[3];
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_cnt[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_cnt[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_cnt[2]);
	std::cout << "Max work groups per compute shader" <<
		" x:" << work_grp_cnt[0] <<
		" y:" << work_grp_cnt[1] <<
		" z:" << work_grp_cnt[2] << "\n";

	int work_grp_size[3];
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1]);
	glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2]);
	std::cout << "Max work group sizes" <<
		" x:" << work_grp_size[0] <<
		" y:" << work_grp_size[1] <<
		" z:" << work_grp_size[2] << "\n";

	int work_grp_inv;
	glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv);
	std::cout << "Max invocations count per work group: " << work_grp_inv << "\n";
}

std::string test::ComputeShader::Load(const char* filename)
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

void test::ComputeShader::OnUpdate(float deltaTime)
{

}

void test::ComputeShader::OnRender(GLFWwindow* window)
{
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(computeProgram);
	glUniform1f(glGetUniformLocation(computeProgram, "test"), testUni);
	glDispatchCompute(ceil(s_widht / 8), ceil(s_height / 4), 1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	glUseProgram(screenShaderProgram);
	glBindVertexArray(VAO);
	glBindTextureUnit(0, screenTex);
	glUniform1i(glGetUniformLocation(screenShaderProgram, "screen"), 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glReadPixels(0, 0, s_widht, s_height, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
}

void test::ComputeShader::OnImGuiRender()
{
	//ImGui::SliderFloat("Radius", &testUni, 0.1f, 3.0f);
	if (ImGui::Button("save"))
	{
		stbi_write_png("testCompute.png", s_widht, s_height, 4, bytes, 4 * s_widht);
	}
}