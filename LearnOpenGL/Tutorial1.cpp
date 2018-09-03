#include "gl.h"
#include "HelloTriangle.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//�����ڴ�С�ı�ʱ�Ļص�����
void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
//����ָ����
void processInput(GLFWwindow *window);

//shader conduct
int CreatShader(GLenum shaderType, const GLchar *const *shaderSource);
void CheckShaderError(int shader);
int CreatShaderProgram(int vertexShader, int fragmentShader);
void CheckShaderLinkError(int shaderProgram);

int main()
{
	//--Init GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Todo ������Щģʽ
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//--Create window
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//ע��ص�����
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

	//--Init GLAD load all opengl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//--Set viewport
	glViewport(0, 0, 300, 300);


	//--Render loop
	while (!glfwWindowShouldClose(window))
	{
		//Input Test
		processInput(window);

		//Render instruction
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glfwSwapBuffers(window);

		//Cheak event
		glfwPollEvents();
	}

	//��ֹ����
	glfwTerminate();


	return 0;
}

void frameBufferSizeCallback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);

}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int CreatShader(GLenum shaderType, const GLchar *const *shaderSource)
{
	int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, shaderSource, NULL);
	glCompileShader(shader);
	CheckShaderError(shader);
	return shader;
}

void CheckShaderError(int shader)
{
	int success = 0; 
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR: shader compilation failed" << infoLog << std::endl;
	}
}

int CreatShaderProgram(int vertexShader, int fragmentShader)
{
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	CheckShaderLinkError(shaderProgram);
	return shaderProgram;
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
