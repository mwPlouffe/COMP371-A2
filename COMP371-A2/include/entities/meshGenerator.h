//
//  MeshGenerator.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-19.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef MeshGenerator_h
#define MeshGenerator_h

#include <vector>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

//generates the normals (vertex) for a given set of vertices and indices

class MeshGenerator
{
	//forward declarations needed for the edge struct
	//these structs are really incestuous and confuse the compiler to no end
	struct Face;
	struct Vertex;
	
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		Vertex(void);
	};
	struct Face
	{
		Vertex *a;
		Vertex *b;
		Vertex *c;
		glm::vec3 fnorm;
	};
	
	std::vector<Vertex*> vertices;
	std::vector<Face*> faces;
	std::vector<GLfloat> normals;
	void init(std::vector<GLfloat> vertexList, std::vector<GLuint> indices, std::vector<GLfloat> normalList);
	public:
		MeshGenerator(void);
		MeshGenerator(std::vector<GLfloat> vertexList, std::vector<GLuint> indices, std::vector<GLfloat> normalList);
		inline std::vector<GLfloat> average_normals(void)
		{
				return normals;
		}
	
		
};

#endif /* MeshGenerator_h */
