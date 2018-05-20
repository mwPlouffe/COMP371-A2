#version 330 core

//info from the renderer, about the object being rendered
in vec3 position_vertex;
in vec3 normal_vertex;
in vec3 colour_vertex;

//debug flag from the renderer
uniform bool disable_shadows;

//camera position, from the camera
uniform vec3 camera_position;

//light information (not all used by the different lights), sent by the light
uniform vec4 position_light;
uniform float ambient_light;
uniform float diffuse_light;
uniform float specular_light;
uniform vec3 colour_light;
uniform vec3 attenuation_constants;

//fragment colour, the output
out vec4 colour;

//intermediate variables
	//ambient
vec3 ambient;

	//diffuse
vec3 lightdir;
float diff;
vec3 diffuse;

	//specular
vec3 viewdir;
float spec;
vec3 reflectdir;
vec3 specular;

	//attentuation
float attn;
float distance;

//temporary variable that allows for distinguishing between point and directional lights
vec3 position_light3;

void main()
{
	if (position_light.w < 0.9f)
	{
		//is a position
		position_light3 = vec3(position_light.x, position_light.y, position_light.z);
	}
	else
	{
		//is a vector
		position_light3 =normalize(-1.0 * vec3(position_light.x, position_light.y, position_light.z) );
	}
	
	//extract the position into a vec3
	
	
	//add the colour to the ambient lighting
	ambient = ambient_light * colour_light;
	
	//calculate the diffuse lighting effects
	lightdir = normalize(position_light3 - position_vertex);
	diff	 = max ( dot(normal_vertex, lightdir), 0);
	diffuse  = diff * colour_light * diffuse_light;
	
	//calculate the specular lighting effects
	viewdir		= normalize(camera_position - position_vertex);
	reflectdir	= reflect(-1*lightdir, normal_vertex);
	spec		= pow( max( dot(viewdir, reflectdir), 0.0), 8);
	specular	= specular_light * spec * colour_light;
	
	
	if (position_light.w < 0.9f)
	{
		//point light, attenuate
		distance = length (position_light3 - position_vertex);
		attn = 1.0f / (attenuation_constants.x + (attenuation_constants.y * distance) + (attenuation_constants.z * distance * distance));
		ambient  *= attn;
		diffuse  *= attn;
		specular *= attn;
	}
	
	//output the fragment colour (with out without the shadows, for debugging purposes)
	if (disable_shadows)
	{
		colour = vec4(colour_vertex, 1.0f);
	}
	else
	{
		colour = vec4(((diffuse + ambient) * colour_vertex), 1.0) + vec4(specular,1.0);
	}
	
}