//
//  pointLight.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-17.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef pointLight_h
#define pointLight_h

#include "light.h"
#include "object.h"
#include "broadcaster.h"
#include "controlAuthority.h"


class PointLight : public Light, public Object, public ControlAuthority
{
	protected:
		glm::vec3 constants;
		glm::vec4 position;
		GLuint pos, attnconsts;
	public:
		PointLight(void);
		PointLight(float ambient, float diffuse, float specular, glm::vec3 colour, glm::vec3 location, glm::vec3 attenuation);
		virtual void updateBounds(std::vector<glm::vec3> frustrumPoints);
		virtual void broadcast(void);
		virtual void init(GLuint shaderID);
		void move(glm::vec3 transform);
	inline virtual glm::vec3 data(void)
	{
		return glm::vec3(position.x, position.y, position.z);
	}
	inline virtual void setData(glm::vec3 data)
	{
		position = glm::vec4(data.x, data.y, data.z, 0.0f);
	}
	virtual glm::mat4 projectionMatrix(void);
	virtual glm::mat4 viewMatrix(void);
	inline virtual void setProjectionMatrix(glm::mat4 projMat)
	{
		projectionMat = projMat;
	}
	virtual void strafe(glm::vec3 direction);
	virtual void rotate(glm::vec3 orientation);
	virtual glm::mat4 update(bool *keys);
};


#endif /* pointLight_h */
