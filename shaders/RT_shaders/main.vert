#version 460 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTex;

out vec2 texCoord;

void main()
{
	texCoord = aTex;
	gl_Position = vec4(aPos, 0.0, 1.0);
}