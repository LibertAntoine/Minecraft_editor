#pragma once

#include <GL/glew.h>
#include <debug_break/debug_break.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>

#ifndef NDEBUG // If DEBUG Flag is active do check (debug_break() is from debug_break lib in vendor)
#define ASSERT(x) if (!x) { debug_break(); assert(false); };
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogError(#x, __FILE__, __LINE__));
#else // Skip the GLCall otherwise
#define GLCall(x) x;
#endif

void GLClearError();
bool GLLogError(const char* function, const char* file, int line);