//
//  mesh.h
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-19.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef mesh_h
#define mesh_h

#include <vector>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

//implements a winged-edge data structure to allow for proper normal computation
class Mesh
{
	//forward declarations needed for the edge struct
	//these structs are really incestuous and confuse the compiler to no end
	struct Face;
	struct Vertex;
	
	struct Edge
	{
		Vertex *curr;
		Face *f;
		Edge* prev, *next;
		Edge* symmetric;
		Edge(Vertex *v);
		Edge(Vertex *v, Edge *prev, Edge *next);
	};
	struct Vertex
	{
		Edge *e;
		glm::vec3 position;
	};
	struct Face
	{
		Edge *e;
	};
	
	std::vector<Edge*> edges;
	std::vector<Vertex*> vertices;
	std::vector<Face*> faces;
	void init(std::vector<GLfloat> vertexList, std::vector<GLuint> indices);
	public:
		Mesh(void);
		Mesh(std::vector<GLfloat> vertexList, std::vector<GLuint> indices);
		std::vector<GLfloat> gouraudNormals(void);
	
		
};

#endif /* mesh_h */
