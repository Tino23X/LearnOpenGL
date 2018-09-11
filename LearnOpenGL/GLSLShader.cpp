#include "GLSLShader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#define LOG_BUFFER_SIZE 1024


GLSLShader::GLSLShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	std::string vertexCode, fragmentCode;
	std::ifstream vertexShaderFile, fragmentShaderFile;

	//ensure ifstream objects can throw exceptions
	vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vertexShaderFile.open(vertexShaderPath);
		fragmentShaderFile.open(fragmentShaderPath);

		//read file
		std::stringstream vertexShaderStream, fragmentShaderStream;
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();

		//close file
		vertexShaderFile.close();
		fragmentShaderFile.close();

		//convert stream into string
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::shader file not succesfully read" << std::endl;
	}

	const char* vShadercode = vertexCode.c_str();
	const char* fShadercode = fragmentCode.c_str();
	
	ID = GetShaderProgram(&vShadercode, &fShadercode);

}

void GLSLShader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void GLSLShader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void GLSLShader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

GLuint GLSLShader::CreatShader(GLenum shaderType, const GLchar* const* shaderSource)
{
	const auto shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, shaderSource, nullptr);
	glCompileShader(shader);
	CheckShaderError(shader);
	return shader;
}

void GLSLShader::CheckShaderError(const int shader)
{
	int success = 0;
	char infoLog[LOG_BUFFER_SIZE];
	//检查编译是否成功
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, LOG_BUFFER_SIZE, nullptr, infoLog);
		std::cout << "ERROR: shader compilation failed" << infoLog << std::endl;
	}

}

void GLSLShader::CheckShaderLinkError(int shaderProgram)
{
	int success = 0;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR: shader link failed" << infoLog << std::endl;
	}
}

GLuint GLSLShader::CreatShaderProgram(int vertexShader, int fragmentShader)
{
	const auto shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	CheckShaderLinkError(shaderProgram);

	//Delete shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

GLuint GLSLShader::GetShaderProgram(const GLchar* const* vertexShaderSource, const GLchar* const* fragmentShaderSource)
{
	const auto vertexShader = CreatShader(GL_VERTEX_SHADER, vertexShaderSource);
	const auto fragmentShader = CreatShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	return CreatShaderProgram(vertexShader, fragmentShader);
}
