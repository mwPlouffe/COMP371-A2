//
//  texture.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-16.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef texture_h
#define texture_h

#include <vector>
#include <iostream>
#define cimg_display 0

#include "CImg.h"
#include "GLException.h"
#include "GLIOException.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

//not currently supporte in the engine
//used as a base for the shadow map

class Texture
{
	public:
		GLuint tex;
		Texture(const char* fp, GLenum DIMS, GLenum COL);
		virtual void init(void);
	
	private:
		bool load(void);
		cimg_library::CImg<unsigned char> texture;
		const char* texturePath;
		std::vector<GLfloat> coordinates;
	protected:
		Texture(GLenum DIMS, GLenum COL);
		GLenum DIM_TYPE;
		GLenum COL_TYPE;
};


#endif /* texture_h */
