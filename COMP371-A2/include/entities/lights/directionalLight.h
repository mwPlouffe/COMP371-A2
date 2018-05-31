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
#include <vector>

//implements a directional light (a light with no position, but a vector direction)
//inherits from the light pure virtual 

class DirectionalLight : public Light
{
	protected:
		glm::vec4 direction;
		GLuint dir;
	public:
		DirectionalLight(void);
		DirectionalLight(float ambient, float diffuse, float specular, glm::vec3 colour, glm::vec3 dir);
		virtual void updateBounds(std::vector<glm::vec3> frustrumPoints);
		virtual void broadcast(void);
		virtual void init(GLuint shaderID);
		void offset(glm::vec3 offset);
		inline virtual glm::vec3 data(void)
		{
			return glm::vec3(direction.x, direction.y,direction.z);
		}
		inline virtual void setData(glm::vec3 data)
		{
			direction = glm::vec4(data.x,data.y,data.z,1.0f);
		}
		virtual glm::mat4 projectionMatrix(void);
		virtual void setProjectionMatrix(glm::mat4 projMat);
		virtual glm::mat4 viewMatrix(void);
	
};

#endif /* directionalLight_h */
