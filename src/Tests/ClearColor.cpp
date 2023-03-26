#include "ClearColor.h"

test::ClearColor::ClearColor()
	: m_Color(glm::vec4(0.2f, 0.3f, 0.7f, 1.0f))
{
}
test::ClearColor::~ClearColor()
{
}
void test::ClearColor::OnUpdate(float deltaTime)
{
}
void test::ClearColor::OnRender()
{
	glClearColor(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}
void test::ClearColor::OnImGuiRender()
{
	ImGui::Begin("ClearColor");
	ImGui::SetWindowFontScale(3.0f);
	ImGui::ColorEdit4("Background", &m_Color.r);
	ImGui::End();
}
