//
//  shadowMap.cpp
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-21.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#include "shadowMap.h"

ShadowMap::ShadowMap(GLenum DIMS, GLenum COLORS, int w, int h)
: Texture(DIMS, COLORS)
{
	width = w;
	height = h;
	glGenTextures(1, &tex);
}
void ShadowMap::init(GLuint dfbo)
{
	//make the frame buffer passed in the current buffer
	glBindFramebuffer(GL_FRAMEBUFFER, dfbo);
	//generate a texture and make it current
	glBindTexture(DIM_TYPE, tex);
	glTexImage2D(DIM_TYPE, 0, COL_TYPE, width, height, 0, COL_TYPE, GL_FLOAT, NULL);
	
	//set the filtering mode to nearest pixel for filtering display
	glTexParameteri(DIM_TYPE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(DIM_TYPE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//have the texture repeat when a coordinate out of bounds is specified
	glTexParameteri(DIM_TYPE, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(DIM_TYPE, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	
	//tell it to output to the texture
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DIM_TYPE, tex, 0);
	
	//when using this buffer, neither read it, or draw it (unnecessary)
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		throw GLException("ERROR: Frame buffer for shadow map not correctly generated");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}