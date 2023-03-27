#include "Renderer.h"

#define WIN_W 1000
#define WIN_H 1000


int main()
{
	Renderer::Render main = Renderer::Render(WIN_W, WIN_H);

	while (main.run())
	{
	}
}