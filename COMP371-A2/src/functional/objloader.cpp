#include "objloader.hpp"

// .OBJ Loader from http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
//modified from the COMP371 tutorial 3 code to work with current project
//see header for changes

#pragma warning(disable:4996)

bool loadOBJ(const char * path, std::vector<GLfloat> &out_vertices, std::vector<GLuint> &out_indices, std::vector<GLfloat> &out_normals)
{
	printf("\tMESSAGE: Loading OBJ file %s...\n", path);

	FILE * file = fopen(path, "r");

	if( file == NULL )
	{
		throw GLIOException("File not found at the specified path");
	}
	while(true)
	{

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			std::cout << "\tMESSAGE: End of File reached for this Object" << std::endl;
			break; // EOF = End Of File. Quit the loop.
		}
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			glm::vec3 vertex;

			int matches = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			
			if (matches != 3)
			{
				throw GLIOException("ERROR: Malformed File. Exiting");
			}

			out_vertices.push_back(vertex.x);
			out_vertices.push_back(vertex.y);
			out_vertices.push_back(vertex.z);

		}
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{

			GLuint idx1, idx2, idx3; //3 indices per line

			int matches = fscanf(file, "%i %i %i\n", &idx1, &idx2, &idx3);

			if (matches != 3)
			{
				throw GLIOException("ERROR: Malformed File. Exiting");
			}

			out_indices.push_back(idx1 - 1); //why -1? hint: look at the first index in teddy.obj
			out_indices.push_back(idx2 - 1);
			out_indices.push_back(idx3 - 1);

		}
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			
			GLfloat idx1, idx2, idx3; //3 normals per line
			
			int matches = fscanf(file, "%f %f %f\n", &idx1, &idx2, &idx3);
			
			if (matches != 3)
			{
				throw GLIOException("ERROR: Malformed File. Exiting");
			}
			
			out_normals.push_back(idx1 );
			out_normals.push_back(idx2 );
			out_normals.push_back(idx3 );
			
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}
	return true;
}
