//
//  pointLight.cpp
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-17.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#include "pointLight.h"

PointLight::PointLight(void)
: Light(),
Object({0.0f, 30.0f, 0.0f}, {0}, {colourLight.r, colourLight.g, colourLight.b})
{
	glm::vec3 location(0.0f, 30.0f, 0.0f);
	//http://wiki.ogre3d.org/-Point+Light+Attenuation
	//location where constants were taken from
	//provides 0% light at 600 units
	position = glm::vec4(0.0f, 50.0f, 0.0f, 0.0f);			//this is a point
	location  = glm::normalize(location);
	
	this->normals.push_back(location.x);
	this->normals.push_back(location.y);
	this->normals.push_back(location.z);
	this->Object::init();
	
	constants.x	= 1.0;
	constants.y	= 0.0014;//14;
	constants.z	= 0.000007;//7;
	
}
PointLight::PointLight(float ambient, float diffuse, float specular, glm::vec3 colour, glm::vec3 location, glm::vec3 attenuation)
: Light(ambient, diffuse, specular, colour),
  Object({location.x, location.y, location.z}, {0}, {colour.r, colour.g, colour.b})
{
	
	constants = attenuation;
	position  = glm::vec4(location.x, location.y, location.z, 0.0f);		//this is a point
	location  = glm::normalize(location);
	
	this->normals.push_back(location.x);
	this->normals.push_back(location.y);
	this->normals.push_back(location.z);
	this->Object::init();
}
void PointLight::broadcast(void)
{
	Light::broadcast();
	glUniform4fv(pos,1,glm::value_ptr(position));
	glUniform3fv(attnconsts,1,glm::value_ptr(constants));
}
void PointLight::init(GLuint shaderID)
{
	Light::init(shaderID);
	pos			= glGetUniformLocation(shaderID,"position_light");
	attnconsts  = glGetUniformLocation(shaderID, "attenuation_constants");
	
	if (-1 == pos || attnconsts == -1)
	{
		throw GLException("PointLight::init -> Could not locate Shader attribute(s). Shaders are not correctly linked.");
	}
}
void PointLight::move(glm::vec3 transform)
{
	//shifts the direction of the directional light field
	position.x += transform.x;
	position.y += transform.y;
	position.z += transform.z;
	vertices = {position.x, position.y, position.z};
	//TODO this requires a rebind of the data!
}