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
#include "meshGenerator.h"
#include "broadcaster.h"
#include "mover.h"

//provided libs
#include "objloader.hpp"

//opengl libs
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

//this class could be considered the mesh class for this engine
//it can load OBJs from file
//it can also generate objects from programmatically given values

class Object : public Broadcaster, public Mover
{
	protected:
		std::vector<GLfloat> vertices;	//0
		std::vector<GLfloat> normals;	//1
		std::vector<GLfloat> colours;	//2
		std::vector<GLuint> indices;
		GLuint tex;
	public:
		GLuint vao;
		GLenum DRAW_MODE;
		//ALL OF THE CONSTRUCTORS FOR ALL THE THINGS!
		Object(void);
		Object(std::vector<GLfloat> vertexList);
	
		//loading the object from file
		Object(const char* filepath);
		Object(std::vector<GLfloat> vertexList,std::vector<GLuint> indexList);
		Object(std::vector<GLfloat> vertexList,std::vector<GLuint> indexList, std::vector<GLfloat> colourList);
		Object(std::vector<GLfloat> vertexList,std::vector<GLuint> indexList, std::vector<GLfloat> normalList, std::vector<GLfloat> colourList);
		std::vector<GLfloat> vertexList(void);
		std::vector<GLfloat> normalList(void);
		std::vector<GLfloat> colourList(void);
		void normalColourise(void);
		void uniformColour(glm::vec3 colour);
		virtual std::vector<GLuint> triangleIndex(void);
		virtual std::vector<GLuint> pointIndex(void);
		virtual void init(void);
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
		//use these to set the object in the world
		virtual void registerToShader(GLuint shaderID);
		virtual void broadcast(void);
		//inherited from the mover behaviour, use this to update the object!
		virtual void move(glm::mat4 transformationMat);
	protected:
		void generateFlatNormals(void);
	private:
		void averageNormals(void);

};


#endif /* object_h */
