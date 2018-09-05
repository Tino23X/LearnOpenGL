// 
// 2018090514:11
// 2018090511:27
// 

#pragma once

#include "gl.h"
#include "gl_extend.h"

typedef void(*RenderFunciton)();
typedef void(*InputCheckFunciton)(GLFWwindow*);


const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const unsigned int GL_MAJOR = 3;
const unsigned int GL_MINOR = 3;

/**
 * \brief Creat GLFW window
 * \return 
 */
GLFWwindow* GLWindowInit();

/**
 * \brief Window Graph render loop
 * \param window 
 * \param color 
 * \param renderFunciton
 * \param inputCheckFunction 
 */
void WindowLoop(GLFWwindow* window, Color4 color, RenderFunciton renderFunciton, InputCheckFunciton inputCheckFunction);