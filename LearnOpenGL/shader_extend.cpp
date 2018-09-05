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


int CreatShader(GLenum shaderType, const GLchar *const *shaderSource)
{
	const int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, shaderSource, nullptr);
	glCompileShader(shader);
	CheckShaderError(shader);
	return shader;
}