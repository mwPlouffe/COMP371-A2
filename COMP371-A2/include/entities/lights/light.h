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

#include <stdio.h>

//an abstraction of the light behaviours - the class itself is not abstract though

class Light : public Broadcaster
{
	protected:
	float ambientLight;
	float diffuseLight;		//light needs a position for this to be useful,
	float specularLight;	//light needs a position for this to be useful
	glm::vec3 colourLight;
	GLuint ambi, diff, spec, col;
	public:
		Light(void);
		Light(float ambient, float diffuse, float specular, glm::vec3 colour);
		virtual void broadcast(void);
		virtual void init(GLuint shaderID);
		
	
};

#endif /* Light_h */
