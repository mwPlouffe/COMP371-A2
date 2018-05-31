//
//  heightMap.h
//  COMP371-A1
//
//  Created by Mathew Plouffe on 2018-05-12.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef heightMap_h
#define heightMap_h

#include "object.h"
#include <iostream>
#define DEFAULT_HEIGHT 400
#define DEFAULT_WIDTH  400
#define DEFAULT_DEPTH  -25

//Height map class from assignment 1
//best used for generating floors and walls in the scene
//inherits several behaviours from the parent class object

class HeightMap : public Object
{
	int width, height;
	public:
	HeightMap(void);
	HeightMap(std::vector<GLfloat> vertices, int w, int h);
	HeightMap(std::vector<GLfloat> vertices, std::vector<GLfloat> colourList, int w, int h);
	virtual std::vector<GLuint>triangleIndex(void);
	virtual std::vector<GLuint>pointIndex(void);
	virtual void init(void);
	void orientNormals(glm::vec3 direction);
	
};
#endif /* heightMap_h */
