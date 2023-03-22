#include "Shapes.h"

std::array<Shapes::Vertex, 4> Shapes::Quad(glm::vec2 location, float size)
{
	Vertex v0;
	v0.Position = { location.x, location.y, 0.0f };

	v0.Color[0] = 1.0f;
	v0.Color[1] = 1.0f;
	v0.Color[2] = 1.0f;
	v0.Color[3] = 1.0f;


	Vertex v1;
	v1.Position = { location.x + size, location.y, 0.0f };
	 
	v1.Color[0] = 1.0f;
	v1.Color[1] = 1.0f;
	v1.Color[2] = 1.0f;
	v1.Color[3] = 1.0f;

	Vertex v2;
	v2.Position = { location.x, location.y - size, 0.0f };
	 
	v2.Color[0] = 1.0f;
	v2.Color[1] = 1.0f;
	v2.Color[2] = 1.0f;
	v2.Color[3] = 1.0f;

	Vertex v3;
	v3.Position = { location.x + size, location.y - size, 0.0f };
	 
	v3.Color[0] = 1.0f;
	v3.Color[1] = 1.0f;
	v3.Color[2] = 1.0f;
	v3.Color[3] = 1.0f;

	return { v0, v1, v2, v3 };
}