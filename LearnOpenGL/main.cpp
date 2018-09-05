#include "window.h"

void RenderFuntion()
{
	std::cout << "RenderFunction..." << std::endl;
}

void InputProcess(GLFWwindow *window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	GLFWwindow *window = GLWindowInit();

	const auto clearColor = GetColor4(0.8f, 0.5f, 0.2f, 1.0f);

	WindowLoop(window, clearColor, RenderFuntion, InputProcess);

	glfwTerminate();

	return 0;
}
