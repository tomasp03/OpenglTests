#version 460 core
layout(location = 0) in vec2 aPos;

uniform float u_scale;

void main()
{
	gl_Position = vec4(u_scale * aPos.x, u_scale * aPos.y, 0.0, 1.0);
}