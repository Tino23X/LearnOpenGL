#pragma once
#include <glad/glad.h>
#include <string>

class GLSLShader
{
public:

	GLuint ID;

	GLSLShader(const char* vertexShaderPath, const char* fragmentShaderPath);

	void Use() const
	{
		glUseProgram(ID);
	}

	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;

private:

	GLuint CreatShader(GLenum shaderType, const GLchar*const * shaderSource);
	void CheckShaderError(const int shader);
	void CheckShaderLinkError(int shaderProgram);
	GLuint CreatShaderProgram(int vertexShader, int fragmentShader);
	GLuint GetShaderProgram(const GLchar*const * vertexShaderSource, const GLchar*const * fragmentShaderSource);
};
