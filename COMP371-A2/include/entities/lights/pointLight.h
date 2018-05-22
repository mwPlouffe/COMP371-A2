//
//  pointLight.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-17.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef pointLight_h
#define pointLight_h

#include "light.h"
#include "object.h"
#include "broadcaster.h"


class PointLight : public Light, public Object
{
	protected:
		glm::vec3 constants;
		glm::vec4 position;
		GLuint pos, attnconsts;
	public:
		PointLight(void);
		PointLight(float ambient, float diffuse, float specular, glm::vec3 colour, glm::vec3 location, glm::vec3 attenuation);
		virtual void broadcast(void);
		virtual void init(GLuint shaderID);
		void move(glm::vec3 transform);
};


#endif /* pointLight_h */
