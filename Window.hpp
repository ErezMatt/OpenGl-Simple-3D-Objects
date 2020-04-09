#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);

	GLint getBufferWidth() const { return bufferWidth; }
	GLint getBufferHeight() const { return bufferHeight; }

	bool getShouldColse() const { return glfwWindowShouldClose(mainWindow); }

	bool getKey(unsigned int keyNum) const;
	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	int init();

	~Window();
private:
	GLFWwindow *mainWindow;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	static const unsigned int NUMBER_OF_KEYS{ 512 };
	bool keys[512];

	GLfloat lastX{ 0 };
	GLfloat lastY{ 0 };
	GLfloat xChange{ 0 };
	GLfloat yChange{ 0 };
	bool mouseFirstMoved{false};
	
	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

