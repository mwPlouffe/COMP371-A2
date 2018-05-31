#ifndef GL_IO_EXCEPTION_H
#define GL_IO_EXCEPTION_H
#include "GLException.h"

//this should be throw when files cannot be found or read
//OBJ file loading, or shader loading

class GLIOException : public GLException
{
	public:
	GLIOException() throw();
	GLIOException(const char* message) throw();
};
#endif
