#pragma once
#include <iostream>
#include <fstream>
#include <glad/glad.h>

class Shader
{
private:
	unsigned int ID;

public:
	Shader(const char* vertSource, const char* fragSource);
	std::string Load(const char* filename);
};

