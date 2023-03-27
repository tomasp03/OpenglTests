#include "Test.h"

test::TestMenu::TestMenu(Test*& currentTestPointer)
	: m_CurrentTest(currentTestPointer)
{
}

void test::TestMenu::OnImGuiRender()
{
	for (auto& test : m_Tests)
	{
		if (ImGui::Button(test.first.c_str()))
		{
			m_CurrentTest = test.second();
		}
	}

	ImGui::Checkbox("Vsync", &isVsync);
}

void test::TestMenu::OnRender(GLFWwindow* window)
{
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
