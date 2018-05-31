//
//  shadowMap.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-21.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef shadowMap_h
#define shadowMap_h

#include "texture.h"
#include "broadcaster.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

//used to track the texture and framebuffer that is attached to it (implemented to get around a memory leak)
//also broadcasts the uniforms to the shaders before rendering the map

class ShadowMap : public Texture
{
	int width, height;
	GLuint targetShaderID;
	GLuint lightViewID, lightProjectionID, lightModelID, shadowBiasID;
	float bias;
	void registerUniforms(void);
	public:
		ShadowMap(GLenum DIMS, GLenum COLORS, int w, int h);
		void updateBias(float value);
		virtual void init(void);
		virtual void broadcast(glm::mat4 lightViewMat, glm::mat4 lightProjectionMat, glm::mat4 lighModelMat);
		void setTargetShader(GLuint shaderID);
		GLuint depthBuffer;
};


#endif /* shadowMap_h */
