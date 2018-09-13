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


//�������⣬������Ҫ��ʱ�빹��
int inds[] = {
	0, 1, 2, //��һ��������
	0, 2, 3 //�ڶ���������
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
		    ��һ������ָ��������Ŀ��(Target)������ΪGL_TEXTURE_2D��ζ�Ż������뵱ǰ�󶨵����������ͬһ��Ŀ���ϵ������κΰ󶨵�GL_TEXTURE_1D��GL_TEXTURE_3D���������ܵ�Ӱ�죩��
		    �ڶ�������Ϊ����ָ���༶��Զ����ļ��������ϣ�������ֶ�����ÿ���༶��Զ����ļ���Ļ�������������0��Ҳ���ǻ�������
		    ��������������OpenGL����ϣ����������Ϊ���ָ�ʽ�����ǵ�ͼ��ֻ��RGBֵ���������Ҳ��������ΪRGBֵ��
		    ���ĸ��͵���������������յ�����Ŀ�Ⱥ͸߶ȡ�����֮ǰ����ͼ���ʱ�򴢴������ǣ���������ʹ�ö�Ӧ�ı�����
		    �¸�����Ӧ�����Ǳ���Ϊ0����ʷ���������⣩��
		    ���ߵڰ˸�����������Դͼ�ĸ�ʽ���������͡�����ʹ��RGBֵ�������ͼ�񣬲������Ǵ���Ϊchar(byte)���飬���ǽ��ᴫ���Ӧֵ��
		    ���һ��������������ͼ�����ݡ�
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
