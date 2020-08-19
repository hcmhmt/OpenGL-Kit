#include "Window.h"
#include <iostream>

using namespace std;

Window::Window() {

	width = 800;
	height = 600;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}

	xChange = 0.0f;
	yChange = 0.0f;

}

Window::Window(GLint windowWidth, GLint windowHeight) {

	width = windowWidth;
	height = windowHeight;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}

	xChange = 0.0f;
	yChange = 0.0f;

}

int Window::initialise() {

	//Initialize GLFW
	if (!glfwInit()) {
		cout << "GLFW initialisation failed!" << endl;
		glfwTerminate();
		return 1;
	}
	cout << "GLFW initialisation is completed!" << endl;

	//Setup GLFW window properties
	//OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //3.3

	//Core profile = No Backwards Compability
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow forward compability
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "SimurgH Window", NULL, NULL);
	if (!mainWindow) {
		cout << "GLFW Window creation failed!" << endl;
		return 1;
	}
	cout << "GLFW Window is created!" << endl;


	//Get Buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//Set context foR GLEW to use
	glfwMakeContextCurrent(mainWindow);

	//Handle key + Mouse input
	createCallbacks();
	//mouse disappear 
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Allow modern extensions features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		cout << "GLFW initialisation failed!" << endl;
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	cout << "GLEW initialisation is completed!" << endl;

	glEnable(GL_DEPTH_TEST);

	int locationX = 0, locationY = 0;
	//Setup Viewport size
	glViewport(locationX, locationY, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks() {
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat Window::getXChange(){
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange(){
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {

	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {

		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
			cout << "Pressed " << key << endl;
		}
		else if (action == GLFW_RELEASE) {
			theWindow->keys[key] = false;
			cout << "Released " << key << endl;
		}

	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos) {

	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved) {
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow ->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	printf("x:%.6f, y:%.6f\n", theWindow->xChange, theWindow->yChange);
}
Window::~Window() {

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
