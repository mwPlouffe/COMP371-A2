//
//  directionalLight.cpp
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-17.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#include "directionalLight.h"

DirectionalLight::DirectionalLight(void)
: Light()
{
	direction = glm::vec4(0.0f, 0.0f, -5.0f, 1.0f);	//light is cast along a vector, not from a point
}
DirectionalLight::DirectionalLight(float ambient, float diffuse, float specular, glm::vec3 colour, glm::vec3 dir) :
Light(ambient, diffuse, specular, colour)
{
	direction = glm::vec4(dir.x, dir.y, dir.z, 1.0f);	//directional light is a vector, not a position
}
void DirectionalLight::broadcast(void)
{
	Light::broadcast();
	glUniform4fv(dir,1,glm::value_ptr(direction));
}
void DirectionalLight::init(GLuint shaderID)
{
	Light::init(shaderID);
	dir = glGetUniformLocation(shaderID,"position_light");
	
	if (dir == -1)
	{
		throw GLException("DirectionalLight::init -> Could not locate Shader attribute(s). Shaders are not correctly linked.");
	}
}
void DirectionalLight::offset(glm::vec3 offset)
{
	//shifts the direction of the directional light field
	direction.x += offset.x;
	direction.y += offset.y;
	direction.z += offset.z;
}