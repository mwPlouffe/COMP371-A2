#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 colour;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

uniform mat4 light_view_matrix;
uniform mat4 light_projection_matrix;
//uniform mat4 light_model_matrix;		//not needed

smooth out vec3 normal_vertex;
out vec3 position_vertex;
out vec3 colour_vertex;
smooth out vec4 lightspace_position;

void main()
{
	//the normal position to pixel transform
	gl_Position		= projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);
	
	//ensures that the normals are not sheared, which leads to undesireable lighting effects
	normal_vertex	= normalize (mat3 (transpose (inverse (model_matrix))) * normal);
	
	//pass the vertex location and colour data forward
	//ensure the position data is oriented correctly in the scene
	position_vertex = vec3(model_matrix * vec4(position, 1.0f));
	colour_vertex	= colour;
	
	//pass the light-space matrix forward to the fragment shader
	lightspace_position = light_projection_matrix * light_view_matrix * vec4(position_vertex, 1.0f);
}