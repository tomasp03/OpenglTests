#include "Shapes.h"

std::array<Shapes::Vertex, 4> Shapes::Quad(glm::vec2 location, float size, glm::vec4 color, float aspectRatio)
{
	Vertex v0;
	v0.Position = { location.x, location.y, 0.0f };
	v0.Color = color;


	Vertex v1;
	v1.Position = { location.x + size, location.y, 0.0f };
	v1.Color = color;

	Vertex v2;
	v2.Position = { location.x, location.y - size * aspectRatio, 0.0f };
	v2.Color = color;

	Vertex v3;
	v3.Position = { location.x + size, location.y - size * aspectRatio, 0.0f };
	v3.Color = color;

	return { v0, v1, v2, v3 };
}