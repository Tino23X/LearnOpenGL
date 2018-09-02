#include "gl.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//当窗口大小改变时的回调函数
void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
//输入指令检测
void processInput(GLFWwindow *window);

int main()
{
	//--Init GLFW
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Todo 还有那些模式
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

	//注册回调函数
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

	//终止函数
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
