//
//  object.cpp
//  COMP371-A1
//
//  Created by Mathew Plouffe on 2018-05-14.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#include "object.h"

//the base type of everything to be rendered in the OGL context
//provides virtual functions for all objects to use dynamically
//allows for only one render and bind function to be used by the renderer

Object::Object(void)
{
	//intentionally empty
	modelMatrix = glm::mat4();
}
Object::Object(std::vector<GLfloat> vertexList)
{
	vertices = vertexList;
	modelMatrix = glm::mat4();
}
Object::Object(std::vector<GLfloat> vertexList,std::vector<GLuint> indexList)
{
	vertices = vertexList;
	indices = indexList;
	modelMatrix = glm::mat4();
}
Object::Object(std::vector<GLfloat> vertexList,std::vector<GLuint> indexList, std::vector<GLfloat> colourList)
{
	vertices = vertexList;
	indices	 = indexList;
	colours	 = colourList;
	modelMatrix = glm::mat4();
}
Object::Object(std::vector<GLfloat> vertexList,std::vector<GLuint> indexList, std::vector<GLfloat> normalList, std::vector<GLfloat> colourList)
{
	vertices = vertexList;
	indices	 = indexList;
	normals  = normalList;
	colours	 = colourList;
	modelMatrix = glm::mat4();
}
std::vector<GLfloat> Object::vertexList(void)
{
	return vertices;
}
//polymorphic, generates a simple ibo that has each vertex being a index
std::vector<GLuint> Object::pointIndex(void)
{
	if (indices.size() != 0)
	{
		return indices;
	}
	int index = 0;
	for (int i = 0; i < vertices.size(); i+=3)
	{
		indices.push_back(index++);
		//std::cout << "(" << vertices[i] << ", " << vertices[i+1] << ", " << vertices[i+2] << ")" << std::endl;
	}
	return indices;
}
//polymorphics, generates the ibo data
std::vector<GLuint> Object::triangleIndex(void)
{
	//intentially left unimplemented, simply returns the points index values
	return indices;
}
std::vector<GLfloat> Object::colourList(void)
{
	return colours;
}
//polymorphic
//populates the ibo data
void Object::init()
{
	if (normals.size() == 0)
	{
		generateFlatNormals();
		averageNormals();
		return;
	}
	std::cout << "\tWARNING: Object::init : Normals already exist for this object, init will not overwrite them." << std::endl;
}
std::vector<GLfloat> Object::normalList(void)
{
	return normals;
}
void Object::normalColourise(void)
{
	colours = normals;
}
void Object::generateFlatNormals(void)
{
	if (normals.size() > 0)
	{
		std::cout << "\tWARNING: Object::generateFlatNormals will not overwrite existing normals. Normals exist for the current object" << std::endl;
		return;
	}
	for (int i = 0; i < indices.size(); i+=3)
	{
		//indices of the vertices in a given triangle
		int va = indices[i];
		int vb = indices[i + 1];
		int vc = indices[i + 2];
		//std::cout << "Triangle: " << i/3 << " (" << va << ", " << vb << ", " << vc << ")" << std::endl;
		
		//each index refers to the first float of a vertex (3 floats per vertex)
		//need to multiply each index by 3 to get vertex index
		va *= 3;
		vb *= 3;
		vc *= 3;
		
//		std::cout << "Vertex Data Start Locations: " << i/3 << " (" << va << ", " << vb << ", " << vc << ")" << std::endl;
//		std::cout << "Vertex Data: " << i     << " (" << vertices[va + 0] << ", " << vertices[va + 1] << ", " << vertices[va + 2] << ")" << std::endl;
//		std::cout << "Vertex Data: " << i + 1 << " (" << vertices[vb + 0] << ", " << vertices[vb + 1] << ", " << vertices[vb + 2] << ")" << std::endl;
//		std::cout << "Vertex Data: " << i + 2 << " (" << vertices[vc + 0] << ", " << vertices[vc + 1] << ", " << vertices[vc + 2] << ")" << std::endl;
		
		//create the vectors
		glm::vec3 ba(vertices[vb] - vertices[va], vertices[vb+1] - vertices[va+1], vertices[vb + 2] - vertices[va + 2]);
		glm::vec3 ca(vertices[vc] - vertices[va], vertices[vc+1] - vertices[va+1], vertices[vc + 2] - vertices[va + 2]);
	
		//std::cout << "Vector BA: (" << ba.x << ", " << ba.y << ". " << ba.z << ") " << std::endl;
		//std::cout << "Vector CA: (" << ca.x << ", " << ca.y << ". " << ca.z << ") " << std::endl;
		
		//generate the normal for the triangle (leave this unnormalised)
		glm::vec3 norm = glm::normalize(( glm::cross(ba, ca) ));
		
		//std::cout << "Face Normal: (" << norm.x << ", " << norm.y << ". " << norm.z << ") " << std::endl << std::endl;
		
		//push the float values of the normal into the std::vector
		normals.push_back(norm.x);
		normals.push_back(norm.y);
		normals.push_back(norm.z);
	}
}
//interface with the objloader
Object::Object(const char* filepath)
{
	//TODO implement the colours and whatnot for the object!
		loadOBJ(filepath, vertices, indices, normals);
}
void Object::uniformColour(glm::vec3 colour)
{
	for (int i = 0; i < vertices.size() ; i+=3)
	{
		colours.push_back(colour.r);
		colours.push_back(colour.g);
		colours.push_back(colour.b);
	}
}
void Object::averageNormals(void)
{
	//generate a poorly named "mesh" to generate the vertex normals
	MeshGenerator *m = new MeshGenerator(vertices, indices, normals);
	this->normals = std::vector<GLfloat>();
	this->normals = m->average_normals();
	free(m);
}
void Object::registerToShader(GLuint shaderID)
{
	modelMatrixID = glGetUniformLocation(shaderID,"model_matrix");
	
	if (modelMatrixID == -1)
	{
		//throw GLException("ERROR: Could not find the model matrix in the shader for an object");
		//this is not unusual, since it could be trying to send data that does not exist
	}
}
void Object::broadcast(void)
{
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}
void Object::move(glm::mat4 transformationMat)
{
	modelMatrix = transformationMat * modelMatrix;
}





