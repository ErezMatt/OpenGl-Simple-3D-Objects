#pragma once

#include <string>

#include <GL/glew.h>

class Shader
{
private:
	std::string readFile(const std::string& fileLocation);

	void compileShader(const std::string& vertexCode, const std::string& fragmentCode);
	void addShader(GLuint theProgram, const std::string& shaderCode, GLenum shaderType);

public:
	Shader();
	Shader(const std::string& vertexCode, const std::string& fragmentCode);

	void createFromString(const std::string& vertexCode, const std::string& fragmentCode);
	void createFromFiles(const std::string& vertexLocation, const std::string& fragmentLocation);

	GLuint getProjectionLocation() const;
	GLuint getModelLocation() const;
	GLuint getViewLocation() const;
	GLuint getAmbientColourLocation() const;
	GLuint getAmbientIntensityLocation() const;

	void use();
	void clear();

	~Shader();

private:
	GLuint shaderID, uniformModel, uniformView, uniformProjection;
	GLuint uniformAmbientColour, uniformAmbientIntensity;
};

