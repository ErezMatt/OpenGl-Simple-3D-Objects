#pragma once

#include <GL\glew.h>

#include <string>

#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(const std::string& fileLocation);

	void load();
	void use();
	void clear();

	~Texture();

private:
	GLuint textureID;
	int width;
	int height;
	int bitDepth;

	std::string fileLocation;
};

