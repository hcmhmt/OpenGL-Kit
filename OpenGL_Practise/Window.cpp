#include "Window.h"
#include <iostream>

using namespace std;

Window::Window() {

	width = 800;
	height = 600;

}

Window::Window(GLint windowWidth, GLint windowHeight) {

	width = windowWidth;
	height = windowHeight;

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

}

Window::~Window() {

	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
