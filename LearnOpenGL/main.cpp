#include "window.h"
#include "shader_extend.h"
#include "buffer_extend.h"
#include "gl_extend.h"
#include "HelloTriangle.h"


const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 fragColor;\n"
	"void main()\n"
	"{\n"
	"	fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
	"}\n\0";


float vers[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};


//法线问题，三角形要逆时针构成
int inds[] = {
	0, 1, 3, //第一个三角形
	1, 2, 3 //第二个三角形
};



void RenderFuntion(GLuint shaderProgram, GLuint VAO)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void InputProcess(GLFWwindow *window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void WindowClearColorSet()
{

	const auto color = GetColor4(0.0f, 0.0f, 0.0f, 1.0f);
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT);

}




int main()
{
	GLFWwindow *window = GLWindowInit();

	const auto shaderProgram = GetShaderProgram(&vertexShaderSource, &fragmentShaderSource);
	GLuint VAO, VBO, EBO;
	GetVAO(VAO, VBO, EBO, vers, sizeof(vers), inds, sizeof(inds));
	
	WindowLoop(window, WindowClearColorSet, RenderFuntion, InputProcess, shaderProgram, VAO);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;
}



