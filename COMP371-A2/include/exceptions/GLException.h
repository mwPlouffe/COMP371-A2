#ifndef GL_EXCEPTION_H
#define GL_EXCEPTION_H

#include <exception>

//throw this when there is an OpenGL problem that is beyond the scope of the programmer to have fixed
//typically silent shader linker errors, unregistered uniforms, and the like

class GLException : public std::exception
{
	//members
	protected:
	const char* mError;
	
	//constructors
	public:
		GLException() throw();
		GLException(const char* message) throw();
		virtual ~GLException() throw(){};
		virtual const char* what()
		{
			return mError;
		}
		
};
#endif
