#pragma once
#include <glad/glad.h>
#include <vector>
#include <functional>
#include <iostream>
#include <imgui.h>
#include <GLFW/glfw3.h>

namespace test
{
	class Test
	{
	public:
		Test() {};
		Test(int w_width, int w_height) {};
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender(GLFWwindow* window){}
		virtual void OnImGuiRender() {}

	protected:
		int width = 0;
		int height = 0;
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu() {};

		void OnImGuiRender() override;
		void OnRender(GLFWwindow* window) override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};
}