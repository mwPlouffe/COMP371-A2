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
	direction = glm::vec4(0.0f, 10.0f, 10.0f, 0.0f);	//light is cast along a vector, not from a point
}
DirectionalLight::DirectionalLight(float ambient, float diffuse, float specular, glm::vec3 colour, glm::vec3 dir) :
Light(ambient, diffuse, specular, colour)
{
	direction = glm::vec4(dir.x, dir.y, dir.z, 0.0f);	//directional light is a vector, not a position
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
void DirectionalLight::updateBounds(std::vector<glm::vec3> frustrumPoints)
{
	//this operation is based on this idea
	//https://gamedev.stackexchange.com/questions/81734/how-to-calculate-directional-light-frustum-from-camera-frustum?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
	
	glm::vec3 viewDir   = glm::normalize(this->data());
	glm::vec3 dummyPos  = this->data();
	glm::vec3 *nearest  = new glm::vec3();
	glm::vec3 *furthest = new glm::vec3();
	
	float nearT  =  10000.0f;
	float farT   = -10000.0f;
	//find the largest and smallest projections along the view vector, these are the
	//closest and furthest points, respectively
	for (int i = 0; i < frustrumPoints.size(); i++)
	{
		if (glm::dot(viewDir, frustrumPoints[i]) < nearT)
		{
			nearest = &frustrumPoints[i];
			nearT = glm::distance(dummyPos, *nearest);
		}
		if (glm::dot(viewDir, frustrumPoints[i]) > farT)
		{
			furthest = &frustrumPoints[i];
			farT = glm::distance(dummyPos, *furthest);
		}
	}
	
	//we now have everything we need to find the desired perpendicular view vectors
	//based off of this thread
	//https://math.stackexchange.com/questions/137362/how-to-find-perpendicular-vector-to-another-vector?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
	
	
	glm::vec3 unitLeft(viewDir.z, 0.0f, -1.0f * viewDir.x );
	glm::normalize(unitLeft);
	glm::vec3 unitTop = glm::normalize (glm::cross(viewDir, unitLeft));
	
	//repeat the process for the left-right planes
	float leftT	 =  -10000.0f;
	float rightT = 10000.0f;
	
	
	for (int i = 0; i < frustrumPoints.size(); i++)
	{
		if (glm::dot(unitLeft, frustrumPoints[i]) > leftT)
		{
			furthest = &frustrumPoints[i];
			leftT	 = glm::distance(dummyPos, *furthest);
		}
		if (glm::dot(unitLeft, frustrumPoints[i]) < rightT)
		{
			nearest = &frustrumPoints[i];
			rightT  = glm::distance(dummyPos, *nearest);
		}
	}
	//and repeat again for the top-bottom planes
	float topT	 =  -10000.0f;
	float bottomT =  10000.0f;
	
	for (int i = 0; i < frustrumPoints.size(); i++)
	{
		if (glm::dot(unitTop, frustrumPoints[i]) < topT)
		{
			furthest = &frustrumPoints[i];
			topT	 = glm::distance(dummyPos, *furthest);
		}
		if (glm::dot(unitTop, frustrumPoints[i]) > bottomT)
		{
			nearest = &frustrumPoints[i];
			bottomT  = glm::distance(dummyPos, *nearest);
		}
	}
	topT = glm::distance(dummyPos, *nearest);
	bottomT  = glm::distance(dummyPos, *furthest);
	
	projectionMat = glm::ortho(-10*leftT, 10*rightT, -10*bottomT, 10*topT, -10*nearT, 10*farT);
}
glm::mat4 DirectionalLight::projectionMatrix(void)
{
	//TODO: this works (in a kinda sketchy way) - it takes the vector as a position, then normalises that vector, and uses the two quantities for the rest of the calculations
	//the main problem with this approach is the hard-coded frustrum 
	
	return projectionMat;
}
glm::mat4 DirectionalLight::viewMatrix(void)
{
	glm::mat4 ret = glm::lookAt(10.0f * this->data(), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
	return ret;
}
void DirectionalLight::setProjectionMatrix(glm::mat4 projMat)
{
	projectionMat = projMat;
}