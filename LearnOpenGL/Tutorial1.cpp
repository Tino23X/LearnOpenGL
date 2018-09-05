#include "gl.h"
#include "HelloTriangle.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//当窗口大小改变时的回调函数
void frameBufferSizeCallback(GLFWwindow *window, int width, int height);
//输入指令检测
void processInput(GLFWwindow *window);

//shader conduct
int CreatShader(GLenum shaderType, const GLchar *const *shaderSource);
void CheckShaderError(int shader);
int CreatShaderProgram(int vertexShader, int fragmentShader);
void CheckShaderLinkError(int shaderProgram);
void GetVAO(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO);

int Main()
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

	int vertexShader = CreatShader(GL_VERTEX_SHADER, &vertexShaderSource);
	int fragmentShader = CreatShader(GL_FRAGMENT_SHADER, &fragmentShaderSource);
	int shaderProgram = CreatShaderProgram(vertexShader, fragmentShader);
	unsigned int VAO, VBO, EBO;
	GetVAO(VAO, VBO, EBO);


	//--Render loop
	while (!glfwWindowShouldClose(window))
	{
		//Input Test
		processInput(window);

		//Render instruction
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);

		//Cheak event
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

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


int CreatShaderProgram(int vertexShader, int fragmentShader)
{
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	CheckShaderLinkError(shaderProgram);

	//Delete shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

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


void GetVAO(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO)
{

	//creat buffers
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	//bind buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	//Copy data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//以顶点属性位置值作为参数，启用顶点属性。
	glEnableVertexAttribArray(0);

	//解绑
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

