#include "Renderer.h"

Renderer::Render::Render(int win_w, int win_h)
{
	double currentFrame = glfwGetTime();
	double lastFrame = currentFrame;
	scene = new test::Squares(win_w, win_h);
}


bool Renderer::Render::run()
{
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	scene->OnUpdate(deltaTime);
	scene->OnRender();
	scene->OnImGuiRender();

	return !glfwWindowShouldClose(scene->WindowID());
}