#pragma once

#include <GL\glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>

#include "Window.hpp"

class Camera
{
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed);
	
	void keyControl(const Window &window, GLfloat dt);
	void mouseControl(GLfloat xChange, GLfloat yChange);
	
	glm::mat4 calculateViewMatrix();

	~Camera();

private: 
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat movmentSpeed;
	GLfloat turnSpeed;
	
	void update();
};

