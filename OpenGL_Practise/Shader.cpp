#include "Shader.h"
using namespace std;

Shader::Shader() {
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {

	CompileShader(vertexCode, fragmentCode);

}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation) {

	string vertexString = ReadFile(vertexLocation);
	string fragmentString = ReadFile(fragmentLocation);

	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);

}

string Shader::ReadFile(const char* fileLocation) {

	string content;
	ifstream fileStream(fileLocation, ios::in);

	if (!fileStream.is_open()) {
		cout << " Failed to read " << fileLocation << "! File does not exist." << endl;
		return "";
	}


	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) {


	shaderID = glCreateProgram();

	if (!shaderID) {
		cout << "Error creating program" << endl;
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		cout << "Error linking program" << eLog << endl;
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		cout << "Error validating program" << eLog << endl;
		return;
	}

	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformView = glGetUniformLocation(shaderID, "view");

}

GLuint Shader::GetProjectionLocation() {

	return uniformProjection;

}

GLuint Shader::GetModelLocation() {

	return uniformModel;

}

GLuint Shader::GetViewLocation() {

	return uniformView;

}

void Shader::UseShader() {
	glUseProgram(shaderID);
}

void Shader::ClearShader() {
	
	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;

}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		cout << "Error compiling the " << shaderType <<  " shader : '" << eLog << "'" << endl;
		return;
	}

	glAttachShader(theProgram, theShader);
}

Shader::~Shader() {
	ClearShader();
}