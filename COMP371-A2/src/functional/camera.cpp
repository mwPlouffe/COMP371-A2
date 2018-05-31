//
//  camera.cpp
//  COMP371-A1
//
//  Created by Mathew Plouffe on 2018-05-15.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#include "camera.h"

//the camera class provides the ability to move the camera around the model, as well as storing useful data on what the camera is looking at

Camera::Camera(void)
{
	//intentionally empty
}
Camera::Camera(glm::vec3 eye, glm::vec3 dir, glm::vec3 up)
{
	position = eye;
	direction = dir;
	orientation = up;
	debug = false;
}
Camera::Camera(glm::vec3 eye, glm::vec3 dir)
{
	position = eye;
	direction = dir;
	orientation = glm::vec3(0.0f,1.0,0.0f);
}
glm::mat4 Camera::init(GLuint shaderID)
{
	//returns a view matrix for the camera
	pos = glGetUniformLocation(shaderID,"camera_position");
	debug_shadows = glGetUniformLocation(shaderID, "disable_shadows");
	if (pos == -1)
	{
		throw GLException("Camera::init -> Could not locate Shader attribute(s). Shaders are not correctly linked.");
	}
	std::cout << "MESSAGE: Camera::init Successful" << std::endl;
	return glm::lookAt(position, direction, orientation);
}
void Camera::broadcast(void)
{
	glUniform3fv(pos,1,glm::value_ptr(position));
	glUniform1i(debug_shadows, debug);
}
void Camera::strafe(glm::vec3 direction)
{
	//generate a translation matrix for the provided direction
	position+=direction;
	this->direction+=direction;
}
void Camera::rotate(glm::vec3 orientation)
{
	//generate a rotation matrix for the provided direction of rotation
	direction+=orientation;
}
glm::mat4 Camera::update(bool *keys)
{
	//this function gathers all the model transforms into one matrix
	//based upon the states provided by the window
	//returns the transformation matrix for use by the renderer
	this->ControlAuthority::update(keys);
	debug = keys[10];
	return glm::lookAt(position,direction, orientation);
}
