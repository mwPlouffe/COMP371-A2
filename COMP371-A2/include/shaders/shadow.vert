#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 colour;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec3 normal_vertex;
out vec3 position_vertex;
out vec3 colour_vertex;

void main()
{
	gl_Position		= projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);
	normal_vertex	= normalize (mat3 (transpose (inverse (model_matrix))) * normal);
	position_vertex = vec3 (model_matrix * vec4(position, 1.0f));
	colour_vertex	= colour;
	
}