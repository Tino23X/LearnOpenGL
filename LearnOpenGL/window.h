// 
// 2018090611:19
// 2018090511:27
// 

#pragma once

#include "gl.h"

typedef void (*RenderFunciton)(GLuint shaderProgram, GLuint VAO);
typedef void (*InputCheckFunciton)(GLFWwindow*);
typedef void (*BackGroundSetFunciton)();


const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const unsigned int GL_MAJOR = 3;
const unsigned int GL_MINOR = 3;

/**
 * \brief Creat GLFW window
 * \return 
 */
GLFWwindow* GLWindowInit();

void WindowLoop(GLFWwindow* window, BackGroundSetFunciton backgroundFunction, RenderFunciton renderFunciton,
                InputCheckFunciton inputCheckFunction, GLuint shaderProgram, GLuint VAO);
