#version 460 core
out vec4 FragColor;

uniform vec2 u_screenSize;

void main()
{
	FragColor =  vec4(gl_FragCoord.x / (u_screenSize.x - 1), gl_FragCoord.y / (u_screenSize.y - 1), 0.25, 1.0);
}