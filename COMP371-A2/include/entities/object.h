//
//  object.h
//  COMP371-A1
//
//  Created by Mathew Plouffe on 2018-05-14.
//  Copyright © 2018 Mathew Plouffe. All rights reserved.
//

#ifndef object_h
#define object_h

//standard libs
#include <vector>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>

//my libs
#include "GLIOException.h"

//provided lib
#include "objloader.hpp"

//opengl libs
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Object
{
	protected:
	std::vector<GLfloat> vertices;	//0
	std::vector<GLfloat> normals;	//1
	std::vector<GLfloat> colours;	//2
	std::vector<GLuint> indices;
	GLuint tex;
	public:
		GLuint vao;
		Object(void);
		Object(std::vector<GLfloat> vertexList);
		Object(std::vector<GLfloat> vertexList,std::vector<GLuint> indexList);
		Object(std::vector<GLfloat> vertexList,std::vector<GLuint> indexList, std::vector<GLfloat> colourList);
		Object(std::vector<GLfloat> vertexList,std::vector<GLuint> indexList, std::vector<GLfloat> normalList, std::vector<GLfloat> colourList);
		std::vector<GLfloat> vertexList(void);
		std::vector<GLfloat> normalList(void);
		std::vector<GLfloat> colourList(void);
		void normalColourise(void);
		void uniformColour(void);
		inline int indexSize(void)
		{
			return indices.size();
		}
		inline int vertexSize(void)
		{
			return vertices.size();
		}
		inline int normalSize(void)
		{
			return normals.size();
		}
		inline int colourSize(void)
		{
			return colours.size();
		}
		virtual std::vector<GLuint> triangleIndex(void);
		virtual std::vector<GLuint> pointIndex(void);
		virtual void generateFlatNormals(void);
		virtual void generateGouraudNormals(void);
		virtual void generatePhongNormals(void);
		virtual void init(void);
	 
	//loading the object from file
		Object(const char* filepath);
};


#endif /* object_h */
