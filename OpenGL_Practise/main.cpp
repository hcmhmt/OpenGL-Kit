#include<stdio.h>
#include<string.h>
#include<cmath>
#include<iostream>
#include<vector>

#include<gl\glew.h>
#include<GLFW\glfw3.h>

#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"

using namespace std;

//Window Dimensions
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
vector<Mesh*> meshList;
vector<Shader> shaderList;

bool direction = true;
float triOffset = 0.0f;
float triMaxoffset = 0.7f;
float triIncrement= 0.0075f;

float curAngle = 0.0f;

bool sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";

//Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void CreateObjects() {
	 
	unsigned int indices[] = {

		0, 3, 1,
		1, 3, 2,
		2, 3, 0, 
		0, 1, 2 

	};

	//triangles coordinates
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		 0.0f, -1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj2);

}

void processInput(GLFWwindow* window) {

	//Close window when press ESC button
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
}

void CreateShaders() {

	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

int main() {

	mainWindow = Window(800, 600);
	mainWindow.initialise();

	CreateObjects();
	CreateShaders();

	GLuint uniformProjection = 0, uniformModel = 0;
	glm::mat4 projection = glm::perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight() , 0.1f, 100.0f);

	// Render loop
	// Loop until window closed
	while (!mainWindow.getShouldClose()) {

		//processInput(mainWindow);

		// Get + Handle user input events
		glfwPollEvents();

		if (direction) {
			triOffset += triIncrement;
		}
		else {
			triOffset -= triIncrement;
		}

		if (abs(triOffset) >= triMaxoffset) {
			direction = !direction;
		}

		curAngle += 1.0f;
		if (curAngle >= 360) {
			curAngle -= 360;
		}

		if (direction) {
			curSize += 0.001f;
		}
		else {
			curSize -= 0.001f;
		}

		if (curSize >= maxSize || curSize <= minSize) {
			sizeDirection = !sizeDirection;
		}

		//Clear window
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();

		glm::mat4 model(1.0f);
	
		// Rotation
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

		// Move
		//model = glm::translate(model, glm::vec3(triOffset, triOffset, 0.0f));

		model = glm::translate(model, glm::vec3(triOffset, -0.5f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f , 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-triOffset, 0.5f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();
		
		
		glUseProgram(0);

		mainWindow.swapBuffers();

	}

	return 0;
}