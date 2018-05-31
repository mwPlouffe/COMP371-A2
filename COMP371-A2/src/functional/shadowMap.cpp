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
	bias = 0.05;
}
void ShadowMap::init(void)
{
	//this links the texture to the framebuffer so that buffer can draw to the texture
	
	//make the frame buffer passed in the current buffer
	glGenFramebuffers(1, &depthBuffer);
	glGenTextures(1, &tex);
	//generate a texture and make it current
	glBindTexture(DIM_TYPE, tex);
	glTexImage2D(DIM_TYPE, 0, GL_DEPTH_COMPONENT32, width, height, 0, COL_TYPE, GL_FLOAT, NULL);
	
	//set the filtering mode to nearest pixel for filtering display
	glTexParameteri(DIM_TYPE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(DIM_TYPE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//have the texture repeat when a coordinate out of bounds is specified
	glTexParameteri(DIM_TYPE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(DIM_TYPE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glBindFramebuffer(GL_FRAMEBUFFER, depthBuffer);
	//tell it to output to the texture
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DIM_TYPE, tex, 0);
	
	//when using this buffer, neither read it, or draw it (unnecessary)
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		throw GLException("ERROR: Frame buffer for shadow map not correctly generated");
	}
	
	//unbind the texture and framebuffer for safety
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void ShadowMap::broadcast(glm::mat4 lightViewMat, glm::mat4 lightProjectionMat, glm::mat4 lightModelMat)
{
	//broadcast each of these matrices to the shaders
	//this data is generated on the fly, so no need to store it
	glUniformMatrix4fv(lightViewID, 1, GL_FALSE, glm::value_ptr(lightViewMat));
	glUniformMatrix4fv(lightProjectionID, 1, GL_FALSE, glm::value_ptr(lightProjectionMat));
	glUniformMatrix4fv(lightModelID, 1, GL_FALSE, glm::value_ptr(lightModelMat));
	glUniform1f(shadowBiasID,bias);
	
}
void ShadowMap::setTargetShader(GLuint shaderID)
{
	//the target of the shader needs to be swapped because the data is needed for both the light and shadow shaders
	targetShaderID = shaderID;
	//need to re-register the uniforms in order to ensure that they are sent to the correct shader
	registerUniforms();
}
void ShadowMap::registerUniforms(void)
{
	lightViewID = glGetUniformLocation(targetShaderID,"light_view_matrix");
	lightProjectionID = glGetUniformLocation(targetShaderID, "light_projection_matrix");
	lightModelID = glGetUniformLocation(targetShaderID, "light_model_matrix");
	shadowBiasID = glGetUniformLocation(targetShaderID, "shadow_bias");
	
	if (lightViewID == -1 || lightProjectionID == -1)
	{
		throw GLException("ERROR: There was an unexpected problem initialising the shadowing shader matrices");
	}
	if (lightModelID == -1 || shadowBiasID == -1)
	{
		//std::cout << "WARNING: The model Matrix could not be registered to the shader. Ensure that this is the desired behaviour" << std::endl;
		//intentionally left empty, the shadow map does not necessarily need the model matrix based on which shader it is directed to use
	}
}
void ShadowMap::updateBias(float value)
{
	bias+=value;
}