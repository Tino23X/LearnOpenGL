// 
// 2018090615:57
// 2018090614:42
// 

#include "window_extend.h"
#include "buffer_extend.h"
#include "gl_extend.h"
#include "GLSLShader.h"
#include <glad/glad.h>
#include "stb_image.h"


float vers[] = {
	//vertiex pos       vertex color		UV
	0.5f, 0.5f, 0.0f,	1.0, 0.0f, 0.0f,	1.0f, 1.0f, // top right
	0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0f,		1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, 0.0, 0.0, 1.0,		0.0f, 0.0f,// bottom left
	-0.5f, 0.5f, 0.0f, 0.0, 1.0, 0.0,		0.0f, 1.0f,// top left 
};


//法线问题，三角形要逆时针构成
int inds[] = {
	0, 1, 2, //第一个三角形
	0, 2, 3 //第二个三角形
};

GLuint texture1, texture2;
/**
 * \brief update uniform variable test
 * \param shaderProgram 
 */
void UniformVariableTest(GLuint shaderProgram)
{
	const auto timeValue = static_cast<float>(glfwGetTime());
	const float offersetValue = (sin(timeValue) * 0.5f) + 0.5f;
	const int outColor = glGetUniformLocation(shaderProgram, "outPosx");
	glUniform1f(outColor, offersetValue);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	
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


void SetTexture()
{
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	// tell stb_image.h to flip loaded texture's on the y-axis.
	stbi_set_flip_vertically_on_load(true);
	auto data = stbi_load("resources/texture/Test1.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		/*
		    第一个参数指定了纹理目标(Target)。设置为GL_TEXTURE_2D意味着会生成与当前绑定的纹理对象在同一个目标上的纹理（任何绑定到GL_TEXTURE_1D和GL_TEXTURE_3D的纹理不会受到影响）。
		    第二个参数为纹理指定多级渐远纹理的级别，如果你希望单独手动设置每个多级渐远纹理的级别的话。这里我们填0，也就是基本级别。
		    第三个参数告诉OpenGL我们希望把纹理储存为何种格式。我们的图像只有RGB值，因此我们也把纹理储存为RGB值。
		    第四个和第五个参数设置最终的纹理的宽度和高度。我们之前加载图像的时候储存了它们，所以我们使用对应的变量。
		    下个参数应该总是被设为0（历史遗留的问题）。
		    第七第八个参数定义了源图的格式和数据类型。我们使用RGB值加载这个图像，并把它们储存为char(byte)数组，我们将会传入对应值。
		    最后一个参数是真正的图像数据。
		 */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "FAILED::Load texture error" << std::endl;
	}

	stbi_image_free(data);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// tell stb_image.h to flip loaded texture's on the y-axis.
	data = stbi_load("resources/texture/Test2.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "FAILED::Load texture error" << std::endl;
	}

	stbi_image_free(data);

}

int main()
{
	GLFWwindow* window = GLWindowInit();
	GLSLShader* shader = new GLSLShader("shader/VertexShader.glsl", "shader/FragmentShader.glsl");
	const auto shaderProgram = shader->ID;
	GLuint VAO, VBO, EBO;
	GetVAO(VAO, VBO, EBO, vers, sizeof(vers), inds, sizeof(inds));

	SetTexture();

	shader->Use();
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
	shader->SetInt("texture2", 1);


	WindowLoop(window, WindowClearColorSet, RenderFuntion, InputProcess, shaderProgram, VAO);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();

	return 0;
}
