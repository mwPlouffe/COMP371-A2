//
//  MeshGenerator.cpp
//  COMP371-A2
//
//  Created by Mathew Plouffe on 2018-05-19.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//


#include "MeshGenerator.h"
MeshGenerator::Vertex::Vertex(void)
{
	//ensure the normal is zeroed out (additive identity)
	normal = glm::vec3(0.0f);
}
MeshGenerator::MeshGenerator(void)
{
	//intentionally left empty
}
MeshGenerator::MeshGenerator(std::vector<GLfloat> vertexList, std::vector<GLuint> indices, std::vector<GLfloat> flatNormals)
{
	//must have the flat normals for this to work correctly
	init(vertexList,indices, flatNormals);
}
void MeshGenerator::init(std::vector<GLfloat> vertexList, std::vector<GLuint> indices, std::vector<GLfloat> flatNormals)
{
	//generate all of the vertices for the MeshGenerator
	for (int i = 0; i < vertexList.size(); i+=3)
	{
		Vertex *v = new Vertex();
		v->position = glm::vec3(vertexList[i], vertexList[i + 1], vertexList[i + 2]);
		vertices.push_back(v);
		//	std::cout << "Vertex: (" << vertexList[i] << ", " << vertexList[i + 1] << ", " << vertexList[i + 2] << ")" << std::endl;
	}
	
	//place all the vertices inside a face (the faces are triangles, so it is done in groups of 3)
	for (int i = 0; i < indices.size(); i+=3)
	{
		Face *f = new Face();
		//add the vertices by the index referred to by the indices std::vector
		f->a = vertices[indices[i	 ]];
		f->b = vertices[indices[i + 1]];
		f->c = vertices[indices[i + 2]];
		
		//each vertex was given the face normal originally, copy that into the face
		f->fnorm = glm::vec3(flatNormals[indices[i	  ]],
							 flatNormals[indices[i + 1]],
							 flatNormals[indices[i + 2]]);
		faces.push_back(f);
//		std::cout << "Face " << i/3 << " Has Vertices:" << std::endl;
//		std::cout << "\tVertex: (" << vertices[indices[i	 ]]->position.x << ", " << vertices[indices[i	 ]]->position.y << ", " << vertices[indices[i	 ]]->position.z << ")" << std::endl;
//		std::cout << "\tVertex: (" << vertices[indices[i	 ]]->position.x << ", " << vertices[indices[i + 1]]->position.y << ", " << vertices[indices[i + 1]]->position.z << ")" << std::endl;
//		std::cout << "\tVertex: (" << vertices[indices[i	 ]]->position.x << ", " << vertices[indices[i + 2]]->position.y << ", " << vertices[indices[i + 2]]->position.y << ")" << std::endl;
//		std::cout << "\tNormal: (" << f->fnorm.x << ", " <<  f->fnorm.y << ", " <<  f->fnorm.z << ")" << std::endl;
	}
	
	//if a vertex appears several times, simply add the old and new normals together
	//the vertices start with the additive identity in them
	for (int i = 0; i < faces.size(); i++)
	{
		faces[i]->a->normal += faces[i]->fnorm;
		faces[i]->b->normal += faces[i]->fnorm;
		faces[i]->c->normal += faces[i]->fnorm;
	}
	
	//now output the correct normals to a std::vector
	//the normals are now on a per-vertex basis, and they should be outputted that way
	
	for (int i = 0; i < vertices.size(); i++)
	{
		//normalise before passing it on
		vertices[i]->normal = glm::normalize(vertices[i]->normal);
		//std::cout << "Vertex: (" << vertices[i]->position.x << ", " << vertices[i]->position.y << ", " << vertices[i]->position.z << ")" << std::endl;
		//std::cout << "\tNormal: (" << vertices[i]->normal.x << ", " <<  vertices[i]->normal.y << ", " <<  vertices[i]->normal.z << ")" << std::endl;
		normals.push_back( vertices[ i ]->normal.x);
		normals.push_back( vertices[ i ]->normal.y);
		normals.push_back( vertices[ i ]->normal.z);
	}
	
	//we now have our average vertex normals
}