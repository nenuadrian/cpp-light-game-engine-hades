#include"shader.h"
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>


// Reads a text file and outputs a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

void Shader::Load(const char* vertexSource, const char* fragmentSource)
{
	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	GL_CHECK(glShaderSource(vertexShader, 1, &vertexSource, NULL));
	// Compile the Vertex Shader into machine code
	GL_CHECK(glCompileShader(vertexShader));
	// Checks if Shader compiled succesfully
	compileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	GL_CHECK(glShaderSource(fragmentShader, 1, &fragmentSource, NULL));
	// Compile the Vertex Shader into machine code
	GL_CHECK(glCompileShader(fragmentShader));
	// Checks if Shader compiled succesfully
	compileErrors(fragmentShader, "FRAGMENT");

	GL_CHECK(ID = glCreateProgram());

	// Attach the Vertex and Fragment Shaders to the Shader Program
	GL_CHECK(glAttachShader(ID, vertexShader));
	GL_CHECK(glAttachShader(ID, fragmentShader));
	// Wrap-up/Link all the shaders together into the Shader Program
	GL_CHECK(glLinkProgram(ID));
	// Checks if Shaders linked succesfully
	GL_CHECK(compileErrors(ID, "PROGRAM"));

	// Delete the now useless Vertex and Fragment Shader objects
	//GL_CHECK(glDeleteShader(vertexShader));
	//GL_CHECK(glDeleteShader(fragmentShader));
}

Shader::Shader() {
}


// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	ID = glCreateProgram();
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();
	Load(vertexSource, fragmentSource);
}


// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (std::string(type) != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
			abort();
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
			abort();
		}
	}
}