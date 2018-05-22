//
//  light.cpp
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-17.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#include "light.h"

Light::Light(void)
{
	ambientLight  = 0.8f;		//0.5
	diffuseLight  =	0.5f;		//0.1
	specularLight = 2.9f;
	colourLight	  = glm::vec3(1.0,1.0,1.0); //white
}
Light::Light(float ambient, float diffuse, float specular, glm::vec3 colour)
{
	ambientLight = ambient;
	diffuseLight = diffuse;
	specularLight = specular;
	colourLight = colour;
}
void Light::broadcast(void)
{
	glUniform1f(ambi, ambientLight);
	glUniform1f(diff, diffuseLight);
	glUniform1f(spec, specularLight);
	glUniform3fv(col, 1, glm::value_ptr(colourLight));
}
void Light::init(GLuint shaderID)
{
	ambi = glGetUniformLocation(shaderID, "ambient_light");
	diff = glGetUniformLocation(shaderID, "diffuse_light");
	spec = glGetUniformLocation(shaderID, "specular_light");
	col  = glGetUniformLocation(shaderID, "colour_light");
	
	if (ambi == -1 || diff == -1 || spec == -1 || col == -1)
	{
		throw GLException("Light::init -> Could not locate Shader attribute(s). Shaders are not correctly linked.");
	}
}
