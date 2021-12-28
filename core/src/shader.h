#pragma once
#include "GL/glew.h"
#include "opengl.h"

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader();
	Shader(const char* vertexFile, const char* fragmentFile);
	void Load(const char* vertexSource, const char* fragmentSource);
private:
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};

