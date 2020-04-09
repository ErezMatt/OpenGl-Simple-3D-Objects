#include "Window.hpp"

#include <iostream>

Window::Window():
	width{800},
	height{600},
	lastX{ 0 },
	lastY{ 0 },
	xChange{ 0 },
	yChange{ 0 },
	mouseFirstMoved{ false }
{
	for (size_t i = 0; i < NUMBER_OF_KEYS; ++i) {
		keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight) :
	width{ windowWidth },
	height{ windowHeight },
	lastX{ 0 },
	lastY{ 0 },
	xChange{ 0 },
	yChange{ 0 },
	mouseFirstMoved{ false }
{
	for (size_t i = 0; i < NUMBER_OF_KEYS; ++i) {
		keys[i] = 0;
	}
}

int Window::init()
{
	if (!glfwInit()) {
		std::cout << "GLFW initialisation failde!";
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Window", NULL, NULL);
	if (!mainWindow) {
		std::cout << "GLFW window creation failed!";
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);

	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW initialisation failed";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, bufferWidth, bufferHeight);
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

bool Window::getKey(unsigned int keyNum) const
{
	if (keyNum >= 0 && keyNum < NUMBER_OF_KEYS) {
		return keys[keyNum];
	}
}

GLfloat Window::getXChange()
{
	GLfloat change = xChange;
	xChange = 0.0f;
	return change;
}

GLfloat Window::getYChange()
{
	GLfloat change = yChange;
	yChange = 0.0f;
	return change;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < NUMBER_OF_KEYS) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	
	if (!theWindow->mouseFirstMoved) {
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = true;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
