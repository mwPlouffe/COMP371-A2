//
//  error.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-22.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef error_h
#define error_h

//If asserted is false, crash mac.
#define ASSERT(x) if (!(x)) asm("int $3");
//Used to error check every opengl call
#define GLCALL(x) clear_errors(); x; ASSERT(handle_gl_errors(#x, __FILE__, __LINE__))

void clear_errors() {
	while (glGetError() != GL_NO_ERROR);
};
bool handle_gl_errors(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "OpenGL Error: " << error << " \nCaused by: " << function << " \nCalled at: " << file << ":" << line << std::endl;
		return false;
	}
	return true;
};


#endif /* error_h */
