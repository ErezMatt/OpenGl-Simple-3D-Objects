#include "Light.hpp"

Light::Light():
	colour{glm::vec3(1.0f, 1.0f, 1.0f)},
	intensity{1.0f}
{
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity):
	colour{glm::vec3(red, green, blue)},
	intensity{intensity}
{
}

void Light::use(GLint intensityLocation, GLint colourLocation)
{
	glUniform3f(colourLocation, colour.x, colour.y, colour.z);
	glUniform1f(intensityLocation, intensity);
}

Light::~Light()
{
}
