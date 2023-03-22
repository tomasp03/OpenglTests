#include"VAO.h"
#include <cstddef>


// Constructor that generates a VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &m_ID);
	Bind();
}

VAO::~VAO()
{
	Delete();
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkVBO(VBO& VBO, GLuint layout, GLint size, GLsizei stride, int offset)
{
	Bind();
	VBO.Bind();
	glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(layout);
	Unbind();
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind()
{
	glBindVertexArray(m_ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &m_ID);
}
