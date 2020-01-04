#pragma once

/**
 * \file GLerror.h
 * \brief Manage the OpenGL error
 * \author Antoine Libert & Nicolas Lienart
 * Launch a break point if an OpenGL error is detected.
 * Print an error message with function, file and line concerned.
 */

#include <GL/glew.h>
#include <debug_break/debug_break.h>
#include <iostream>
#include <assert.h>

/**
* \brief Launch a break point if OpenGL Error appear (on Windows Visual Studio and Linux)
*/
#ifndef NDEBUG // If DEBUG Flag is active do check (debug_break() is from debug_break lib in vendor)
#define ASSERT(x) if (!x) { debug_break(); assert(false); };
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogError(#x, __FILE__, __LINE__));
#else // Skip the GLCall otherwise
#define GLCall(x) x;
#endif

/**
* \brief Clean the OpenGL error list
*/
void GLClearError();

/**
* \brief Print an error message with information relatives of the OpenGL error.
* \param *function name of the function which lauch the OpenGLerror.
* \param *file the file which we can find this fonction.
* \param line the line of the function in the file.
*/
bool GLLogError(const char* function, const char* file, int line);