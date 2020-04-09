#include "Shader.hpp"

#include <iostream>
#include <fstream>

Shader::Shader():
	shaderID {0},
	uniformModel {0},
	uniformView	{0},
	uniformProjection {0}
{
}

Shader::Shader(const std::string& vertexCode, const std::string& fragmentCode) :
	shaderID {0},
	uniformModel {0},
	uniformView {0},
	uniformProjection {0}
{
	createFromFiles(vertexCode, fragmentCode);
}

void Shader::createFromString(const std::string& vertexCode, const std::string& fragmentCode)
{
	compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const std::string& vertexLocation, const std::string& fragmentLocation)
{
	std::string vertexCode = readFile(vertexLocation);
	std::string fragmentCode = readFile(fragmentLocation);

	compileShader(vertexCode, fragmentCode);
}

std::string Shader::readFile(const std::string& fileLocation)
{
	std::string text;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		std::cout << "Failed to open file";
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		text.append(line + "\n");
	}

	fileStream.close();
	return text;
}

void Shader::compileShader(const std::string& vertexCode, const std::string& fragmentCode)
{
	shaderID = glCreateProgram();

	if (!shaderID) {
		std::cout << "Error creating shader program!" << std::endl;
		return;
	}
	addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		std::cout << "Error linkink program!" << std::endl;
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		std::cout << "Error validating program!" << std::endl;
		return;
	}

	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformAmbientColour = glGetUniformLocation(shaderID, "directionalLight.colour");
	uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.intensity");
}

GLuint Shader::getProjectionLocation() const
{
	return uniformProjection;
}

GLuint Shader::getModelLocation() const
{
	return uniformModel;
}

GLuint Shader::getViewLocation() const
{
	return uniformView;
}

GLuint Shader::getAmbientColourLocation() const
{
	return uniformAmbientColour;
}

GLuint Shader::getAmbientIntensityLocation() const
{
	return uniformAmbientIntensity;
}

void Shader::use()
{
	glUseProgram(shaderID);
}

void Shader::clear()
{
	if(shaderID != 0){
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
	uniformModel = 0;
	uniformView = 0;
	uniformProjection = 0;
	uniformAmbientColour = 0;
	uniformAmbientIntensity = 0;
}

void Shader::addShader(GLuint program, const std::string& shaderCode, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	const GLchar* codeC;
	codeC = shaderCode.c_str();

	GLint codeLength;
	codeLength = shaderCode.length();

	glShaderSource(shader, 1, &codeC, &codeLength);
	glCompileShader(shader);

	GLint result = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result) {
		std::cout << "Error compiling program!" << shaderType << std::endl;
		return;
	}
	glAttachShader(program, shader);
}

Shader::~Shader()
{
	clear();
}
