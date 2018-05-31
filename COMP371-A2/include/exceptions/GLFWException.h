#ifndef GLFW_EXCEPTION_H
#define GLFW_EXCEPTION_H
#include <exception>

//this should really only be thrown once per run of the program, when the window attempts to instantiate glfw

class GLFWException : public std::exception
{
	protected:
		const char* mError;
	
	public:
		GLFWException() throw();
		virtual ~GLFWException() throw() {};
		GLFWException(const char* message) throw();
		virtual const char* what() const throw()
		{
			return mError;
		};
};
#endif
