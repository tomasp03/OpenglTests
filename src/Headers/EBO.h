#pragma once
#include <glad/glad.h>

class EBO
{
private:
	GLuint m_ID;

public:
	EBO(GLuint* indices, GLsizeiptr size);
	~EBO();
	void Bind();
	void Unbind();
	void Delete();
};
