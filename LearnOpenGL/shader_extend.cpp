#include "shader_extend.h"

void CheckShaderError(const int shader)
{
	int success = 0; 
	char infoLog[512];
	//检查编译是否成功
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "ERROR: shader compilation failed" << infoLog << std::endl;
	}
}


GLuint CreatShader(GLenum shaderType, const GLchar *const *shaderSource)
{
	const auto shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, shaderSource, nullptr);
	glCompileShader(shader);
	CheckShaderError(shader);
	return shader;
}


void CheckShaderLinkError(int shaderProgram)
{
	int success = 0; 
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR: shader link failed" << infoLog << std::endl;
	}
}

GLuint CreatShaderProgram(int vertexShader, int fragmentShader)
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

GLuint GetShaderProgram(const GLchar *const *vertexShaderSource, const GLchar *const *fragmentShaderSource)
{
	const auto vertexShader = CreatShader(GL_VERTEX_SHADER, vertexShaderSource);
	const auto fragmentShader = CreatShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	return CreatShaderProgram(vertexShader, fragmentShader);
}