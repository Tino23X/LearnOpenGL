// 
// 2018090615:57
// 2018090614:42
// 

#include "window_extend.h"
#include "shader_extend.h"
#include "buffer_extend.h"
#include "gl_extend.h"


const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aColor;\n"
	"out vec4 vectorColor;"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos, 1.0);\n"
	"   vectorColor = vec4(aColor, 1.0);\n"
	"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 fragColor;\n"
	"in vec4 vectorColor;"
	"uniform vec4 outColor;"
	"void main()\n"
	"{\n"
	"	fragColor = vectorColor;"
	"}\n\0";


float vers[] = {
	0.5f, 0.5f, 0.0f, 1.0, 0.0f, 0.0f, // top right
	0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, 0.0, 0.0, 1.0,// bottom left
	-0.5f, 0.5f, 0.0f, 0.0, 1.0, 0.0 // top left 
};


//法线问题，三角形要逆时针构成
int inds[] = {
	0, 1, 2, //第一个三角形
	0, 2, 3 //第二个三角形
};

/**
 * \brief update uniform variable test
 * \param shaderProgram 
 */
void UniformVariableTest(GLuint shaderProgram)
{
	const float timeValue = glfwGetTime();
	const float greenValue = (sin(timeValue) * 0.5f) + 0.5f;
	const int outColor = glGetUniformLocation(shaderProgram, "outColor");
	glUniform4f(outColor, 0.0f, greenValue, 0.0f, 1.0f);
	
}


void RenderFuntion(GLuint shaderProgram, GLuint VAO)
{
	UniformVariableTest(shaderProgram);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void InputProcess(GLFWwindow* window)
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
	GLFWwindow* window = GLWindowInit();

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
