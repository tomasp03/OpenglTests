#pragma once
#include<glad/glad.h>
#include"VBO.h"

class VAO
{
private:
	GLuint m_ID;

public:
	// ID reference for the Vertex Array Object
	// Constructor that generates a VAO ID
	VAO();
	~VAO();

	// Links a VBO to the VAO using a certain layout
	void LinkVBO(VBO& VBO, GLuint layout);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};

