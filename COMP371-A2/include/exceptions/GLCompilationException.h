#ifndef GL_COMPILATION_EXCEPTION_H
#define GL_COMPILATION_EXCEPTION_H
#include "GLException.h"

//only throw this when the shaders cannot compile (an error external to the program)

class GLCompilationException : public GLException
{
	public:
	GLCompilationException() throw();
	GLCompilationException(const char* message) throw();
};
#endif
