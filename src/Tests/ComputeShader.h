#include "Test.h"
#include <fstream>

#include<stb/stb_image_write.h>

namespace test
{
	class ComputeShader : public Test
	{
	private:
		GLuint computeShader;
		GLuint computeProgram;
		GLuint program;
		GLuint screenTex;

		GLuint VAO;

		GLuint screenShaderProgram;
		GLuint screenVertexShader;
		GLuint screenFragmentShader;

		unsigned char* bytes;

		float testUni = 1.0f;

		int s_widht = 1200;
		int s_height = 1200;

	public:
		ComputeShader();
		void OnUpdate(float deltaTime) override;
		void OnRender(GLFWwindow* window) override;
		void OnImGuiRender() override;


		std::string Load(const char* filename);
	};
}