#pragma once

#include "GLInclude.h"
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(x) ClearErrors(); x; LogErrors(#x, __FILE__, __LINE__)

static void ClearErrors()
{
	while (glGetError() != 0);
}

static void LogErrors(const char* function, const char* file, int line)
{
	while (GLenum err = glGetError())
	{
		std::cout << "OpenGL Error (" << err << ") " << function << " " << file << ": " << line << std::endl;
	}
}