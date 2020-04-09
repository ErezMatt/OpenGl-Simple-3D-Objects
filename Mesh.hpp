#pragma once

#include <GL/glew.h>

#include <glm\glm.hpp>

#include <vector>

struct Vertex 
{
	glm::vec3 position;
	glm::vec2 texCoords;	
};

class Mesh
{
public:
	Mesh();
	Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);

	void create(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
	void render();
	void clear();

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

