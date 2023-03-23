#pragma once
#include <iostream>
#include <array>
#include <glm/glm.hpp>

namespace Shapes
{
	struct Vertex
	{
	public:
		glm::vec3 Position;
		glm::vec4 Color;
	};

	std::array<Vertex, 4> Quad(glm::vec2 location, float size, glm::vec4 color, float aspectRatio);
}