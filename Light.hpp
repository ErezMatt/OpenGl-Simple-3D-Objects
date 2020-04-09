#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intinsity);
	
	void use(GLint intensityLocation, GLint colourLocation);

	~Light();

private:
	glm::vec3 colour;
	GLfloat intensity;
};

