#pragma once

#include <string>
#include <cmath>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Light.hpp"


class Application
{
public:
	Application();
	~Application();

	void run();
	void update();

private:
	Window mainWindow;
	Shader shader;
	Camera camera;
	Light mainLight;

	Texture metalTexture;

	std::vector<std::unique_ptr<Mesh>> meshList;
	std::vector<Shader> shaderList;

public:
	const float TO_RADIANS = 3.14159265f / 180.0f;
	
	const std::string vShader = "Shaders/shader.vert";
	const std::string fShader = "Shaders/shader.frag";
};

