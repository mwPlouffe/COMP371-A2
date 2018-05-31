//
//  spotLight.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-17.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef spotLight_h
#define spotLight_h

#include "pointLight.h"

//implements a spot light, which is a combination of the behaviours of a point and directional light
//inherits from both point and spot lights
//emits light in a cone from the point specified
//INCOMPLETE

class SpotLight : public PointLight, public directionalLight
{
	float maxAngle;		//perspective matrix FOV
	bool softEdges;		//idk about this one yet lol
	public:
		SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, glm::vec3 direction, float c, float l, float q, float angle, bool soft);
		SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, glm::vec3 direction, bool soft);
		virtual void updateBounds(std::vector<glm::vec3> frustrumPoints)=0;
		virtual void broadcast(void)=0;
		virtual void init(GLuint shaderID)=0;
		inline virtual glm::vec3 data(void)
		{
			return glm::vec3(position.x, position.y, position.z);
		}
		virtual glm::mat4 projectionMatrix(void)=0;
		virtual glm::mat4 viewMatrix(void)=0;
};


#endif /* spotLight_h */
