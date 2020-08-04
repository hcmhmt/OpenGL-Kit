#pragma once

#include<GL\glew.h>

class Mesh
{
public:
	Mesh();

	void CreateMesh(GLfloat *vertices, unsigned int *indeces, unsigned int numOfVertices, unsigned int numOfIndices );
	void RenderMesh();
	void ClearMesh();

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

