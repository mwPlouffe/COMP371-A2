//
//  light.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-17.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef Light_h
#define Light_h

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GLException.h"
#include "broadcaster.h"
#include <vector>

#include <stdio.h>

//an abstraction of the light behaviours - the class is pure virtual to reflect this
//NB: does provide some constructors and functions that are used or overriden by its children

class Light : public Broadcaster
{
	protected:
	float ambientLight;
	float diffuseLight;		//light needs a position for this to be useful,
	float specularLight;	//light needs a position for this to be useful
	glm::vec3 colourLight;
	glm::mat4 projectionMat;

	GLuint ambi, diff, spec, col;
	public:
		Light(void);
		Light(float ambient, float diffuse, float specular, glm::vec3 colour);
		virtual void broadcast(void);
		virtual void init(GLuint shaderID);
		virtual glm::mat4 projectionMatrix(void)=0;
		virtual glm::mat4 viewMatrix(void)=0;
		virtual glm::vec3 data(void)=0;
		virtual void updateBounds(std::vector<glm::vec3> frustrumPoints)=0;
		virtual void setProjectionMatrix(glm::mat4 projMat)=0;
		inline virtual void setData(glm::vec3 data)=0;
		
	
};

#endif /* Light_h */
