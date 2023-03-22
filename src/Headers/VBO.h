#pragma once
#include <glad/glad.h>

class VBO
{
private:
	unsigned int m_ID;

public:
	VBO(GLfloat* vertices, GLsizeiptr size);
	~VBO();
	void Bind();
	void Unbind();
	void Delete();
};

