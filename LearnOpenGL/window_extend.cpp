// 
// 2018090615:57
// 2018090510:43
// 

#include "window_extend.h"

void GLFWInit(const int major, int minor)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


GLFWwindow* CreatWindow(const char* title, GLFWframebuffersizefun cbfun)
{
	const auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title, nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "FAILED :: creat GLFW window error!!!";
		glfwTerminate();
		return nullptr;
	}

	//Bind window to context
	glfwMakeContextCurrent(window);

	//register fram buffer callback
	glfwSetFramebufferSizeCallback(window, cbfun);

	return window;
}


void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void GladLoader()
{
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "FAILED :: GLAD loader error!!!";
		glfwTerminate();
	}
}

GLFWwindow* GLWindowInit()
{
	GLFWInit(GL_MAJOR, GL_MINOR);
	GLFWwindow* window = CreatWindow("OpenGLLearn", FrameBufferSizeCallback);
	GladLoader();

	return window;
}


void WindowLoop(GLFWwindow* window, BackGroundSetFunciton backgroundFunction, RenderFunciton renderFunciton,
                InputCheckFunciton inputCheckFunction, GLuint shaderProgram, GLuint VAO)
{
	while (!glfwWindowShouldClose(window))
	{
		inputCheckFunction(window);

		backgroundFunction();

		renderFunciton(shaderProgram, VAO);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
