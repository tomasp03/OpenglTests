#include "Loader.h"
#include "Renderer.h"

#define WIN_W 1200
#define WIN_H 1200


int main()
{
	Renderer::Render main = Renderer::Render(WIN_W, WIN_H);

	while (main.run())
	{
	}
}