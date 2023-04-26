#include "Renderer.h"

#define WIN_W 800
#define WIN_H 800


int main()
{
	Renderer::Render main = Renderer::Render(WIN_W, WIN_H);

	while (main.run())
	{
	}
}