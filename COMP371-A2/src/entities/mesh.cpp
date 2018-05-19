//
//  mesh.cpp
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-19.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//


#include "mesh.h"
Mesh::Edge::Edge(Vertex *v)
{
	this->curr = v;
}
Mesh::Edge::Edge(Vertex *v, Edge *prev, Edge *next)
{
	this->curr= v;
	this->prev = prev;
	this->next = next;
}
Mesh::Mesh(void)
{
	//intentionally left empty
}
Mesh::Mesh(std::vector<GLfloat> vertexList, std::vector<GLuint> indices)
{
	init(vertexList,indices);
}
std::vector<GLfloat> Mesh::gouraudNormals(void)
{
	return (std::vector<GLfloat>) NULL;
}

//https://people.cs.clemson.edu/~dhouse/courses/405/papers/winged-edge.pdf
//implementation of the winged-edge ADT for
void Mesh::init(std::vector<GLfloat> vertexList, std::vector<GLuint> indices)
{
	//generate all of the vertices for the mesh, with appropriate indexing
	for (int i = 0; i < vertexList.size(); i+=3)
	{
		Vertex *v;
		v->position = glm::vec3(vertexList[i], vertexList[i + 1], vertexList[i + 2]);
		vertices.push_back(v);
		//index is divided by 3 since each vec3 requires 3 values
	}
	
	//generate the edges as dictated by the indices std::vector
	//indices directly correspond to the position of a vertex in the std::vector
	for (int i = 0; i < indices.size(); i+=3)
	{
		//create the edges of the triangle
		Edge *e1;
		Edge *e2;
		Edge *e3;
		
		//create a new face container
		Face *f = new Face();;
		
		//link the edges together (generating a new edge object for the pointer
		e1 = new Edge(vertices[indices[i	]], e3, e2);
		e2 = new Edge(vertices[indices[i + 1]], e1, e3);
		e3 = new Edge(vertices[indices[i + 2]], e2, e1);
		
		//generate the symmetric edge for each edge
		
		//link the vertices to their edges
		vertices[indices[i	  ]] ->e = e1;
		vertices[indices[i + 1]] ->e = e2;
		vertices[indices[i + 2]] ->e = e3;
		
		//create the face container and store it by value
		f->e = e1;
		faces.push_back(f);
		
		//store the edges by value
		edges.push_back(e1);
		edges.push_back(e1);
		edges.push_back(e1);
	}
	//the mesh should be complete at this point, allowing for constant access to
	
	
}