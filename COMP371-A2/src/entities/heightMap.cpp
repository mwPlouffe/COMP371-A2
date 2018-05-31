//
//  heightMap.cpp
//  COMP371-A1
//
//  Created by Mathew Plouffe on 2018-05-12.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#include "heightMap.h"

//inherits from object
//generates a map from the provided data, as well as the width and height of the map

HeightMap::HeightMap(void) : Object()
{
	//generate a generic, flat, height map!
	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT;
	for (int x = -1 * width/2; x < width/2; x++)
	{
		for (int z = -1 * height/2 ; z < height/2; z++)
		{
			vertices.push_back(x);
			vertices.push_back(DEFAULT_DEPTH);
			vertices.push_back(z);
		}
	}
}
HeightMap::HeightMap(std::vector<GLfloat> vertices, int w, int h)
:Object(vertices)
{
	width = w;
	height = h;
}
HeightMap::HeightMap(std::vector<GLfloat> vertices,std::vector<GLfloat> colourList, int w, int h)
: Object(vertices)
{
	width = w;
	height = h;
	colours = colourList;
}
//poylmorphic
//generates the ibo data required to render the surface using triangles
std::vector<GLuint>HeightMap::triangleIndex(void)
{
	//used the algorithm presented in this tutorial for the triangle generation
	//https://research.ncl.ac.uk/game/mastersdegree/graphicsforgames/indexbuffers/Tutorial%208%20-%20Index%20Buffers.pdf
	
	for (int x = 0; x < width - 1; x++)
	{
		for (int z = 0; z < height - 1; z++)
		{
			GLuint a =( x		* (height)) +  z;
			GLuint b =((x+1)	* (height)) +  z;
			GLuint c =((x+1)	* (height)) + (z + 1);
			GLuint d =( x		* (height)) + (z + 1);
			
			indices.push_back(a);
			indices.push_back(d);
			indices.push_back(b);
			//std::cout << "(" << c << ", " << b << ", " << a << ")" << "\t(" << x << ", " << z << ")" << std::endl;
			indices.push_back(b);
			indices.push_back(d);
			indices.push_back(c);
			//std::cout << "(" << c << ", " << a << ", " << d << ")" << "\t(" << x << ", " << z << ")" << std::endl;
		}
	}
	return indices;
}

//returns the Base object version point index, not need to do anything else
std::vector<GLuint>HeightMap::pointIndex(void)
{
		return Object::pointIndex();
}

//populates the ibo data before it is bound
void HeightMap::init(void)
{
	triangleIndex();
	Object::generateFlatNormals();
}
void HeightMap::orientNormals(glm::vec3 direction)
{
	for (int i = 0 ; i < normals.size(); i+=3)
	{
		if (direction.x != 0)
		{
			normals[i] *= direction.x;
		}
		if (direction.y != 0)
		{
			normals[i + 1] *= direction.y;
		}
		if (direction.z != 0)
		{
			normals[i + 2] *= direction.z;
		}
		//std::cout << "(" << normals[i] << ", " << normals[i + 1] << ", " << normals[i + 2] << ")" << "\t(" << i/3 << ")" << std::endl;
	}
}



