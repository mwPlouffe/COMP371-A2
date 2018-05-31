//
//  mover.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-30.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef mover_h
#define mover_h

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Mover
{
	protected:
		glm::mat4 modelMatrix;			//used to move the object around in space
		GLuint modelMatrixID;			//register in the shader as the valid model matrix
	public:
		Mover(void){ modelMatrix=glm::mat4(); };					//instantiate the model matrix to be the identity matrix (default constructor behaviour for glm)
		virtual void move(glm::mat4 transformationMat)=0;		//apply this transformation matrix to the current model matrix
	
	
};

#endif /* mover_h */
