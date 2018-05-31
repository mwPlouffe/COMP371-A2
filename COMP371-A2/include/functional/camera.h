//
//  camera.h
//  COMP371-A1
//
//  Created by Mathew Plouffe on 2018-05-15.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "window.h"
#include "object.h"
#include "broadcaster.h"
#include "controlAuthority.h"

//the camera of the engine
//tracks the position and state of the view of the scene
//TODO have this class broadcast the view matrix to the shaders as required.

class Camera : public Broadcaster, public ControlAuthority
{
	glm::vec3 position, direction, orientation;
	GLuint pos, debug_shadows;
	bool debug;
	public:
		Camera(void);
		Camera(glm::vec3 eye, glm::vec3 dir, glm::vec3 up);
		Camera(glm::vec3 eye, glm::vec3 dir);
		virtual glm::mat4 update(bool *keys);
		glm::mat4 init(GLuint shaderID);
		virtual void broadcast(void);
	protected:
		virtual void strafe(glm::vec3 direction);
		virtual void rotate(glm::vec3 orientation);
};


#endif /* camera_h */
