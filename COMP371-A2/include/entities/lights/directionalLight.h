//
//  directionalLight.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-17.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef directionalLight_h
#define directionalLight_h

#include "light.h"

class DirectionalLight : public Light
{
	protected:
		glm::vec4 direction;
		GLuint dir;
	public:
		DirectionalLight(void);
		DirectionalLight(float ambient, float diffuse, float specular, glm::vec3 colour, glm::vec3 dir);
		virtual void broadcast(void);
		virtual void init(GLuint shaderID);
		void offset(glm::vec3 offset);
	
};

#endif /* directionalLight_h */
