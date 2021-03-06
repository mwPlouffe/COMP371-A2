#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <vector>
#include <GL/glew.h>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <regex>
#include "GLIOException.h"

//modified from the COMP371 tutorial 3 code to work with current project
//			--bad IO throws exception
//			--supports normals

bool loadOBJ(
	const char * path, 
	std::vector<GLfloat> &out_vertices,
	std::vector<GLuint> &out_indices,
	std::vector<GLfloat> &out_normals
);

#endif