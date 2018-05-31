//
//  controlAuthority.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-29.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef controlAuthority_h
#define controlAuthority_h

#include "glm/glm.hpp"

//pure virtual class that allows children to respond to 

class ControlAuthority
{
	public:
		ControlAuthority(void){};
		virtual ~ControlAuthority(void){};
		virtual glm::mat4 update(bool *keys)
		{
			//this function gathers all the model transforms into one matrix
			//based upon the states provided by the window
			//returns the transformation matrix for use by the renderer
			
			if (keys[0] == true)
			{
				//up
				strafe( glm::vec3(0.0f,2.0f,0.0f));
			}
			if (keys[1] == true)
			{
				//down
				strafe( glm::vec3(0.0f,-2.0f,0.0f) );
			}
			if (keys[2] == true)
			{
				//left
				strafe(glm::vec3(-2.0f,0.0f,0.0f));
			}
			if (keys[3] == true)
			{
				//right
				strafe(glm::vec3(2.0f,0.0f,0.0f));
			}
			if (keys[4] == true)
			{
				//zoom in
				strafe(glm::vec3(0.0f,0.0f,2.0f));
			}
			if (keys[5] == true)
			{
				//zoom out
				strafe(glm::vec3(0.0f,0.0f,-2.0f));
			}
			if (keys[6] == true)
			{
				//rotate down-up
				rotate(glm::vec3(0.0f,4.0f,0.0f));
			}
			if (keys[7] == true)
			{
				//rotate right-left
				rotate(glm::vec3(-4.0f,0.0f,0.0f));
			}
			if (keys[8] == true)
			{
				//rotate up-down
				rotate(glm::vec3(.0f,-4.0f,0.0f));
			}
			if (keys[9] == true)
			{
				//rotate left-right
				rotate(glm::vec3(4.0f,0.0f,0.0f));
			}
			return glm::lookAt(glm::vec3(),glm::vec3(), glm::vec3());
		}
	protected:
		virtual void strafe(glm::vec3 direction)=0;
		virtual void rotate(glm::vec3 orientation)=0;
};
#endif /* controlAuthority_h */
