#version 330 core

//info from the renderer, about the object being rendered
in vec3 position_vertex;
in vec3 colour_vertex;
smooth in vec3 normal_vertex;

//debug flag from the renderer
uniform bool disable_shadows;
uniform float shadow_bias;
float bias;

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

//unit normal of the interpolated vertex normals
vec3 norm;

float z;
float depthValue;
float LinearizeDepth(float depth)
{
	z = depth * 2.0 - 1.0; // Back to NDC
	return (2.0 * 0.1f * 200.f) / (0.1f+ 200.f- z * (200.f - 0.1f));
}





//temporary variable that allows for distinguishing between point and directional lights
vec3 position_light3;
//temporary variables for generating shadows
vec3 projection_coordinates;
float closest;
float current;

//shadow map information
uniform sampler2D shadow_map;
smooth in vec4 lightspace_position;

float generateShadows(vec4 fragment_lightspace_position, float bias)
{
	//place the prospective pixel into lightspace
	projection_coordinates = fragment_lightspace_position.xyz / fragment_lightspace_position.w;
	
	//ensures that the transformed value is within the [0,1] bracket of the shadow texture
	projection_coordinates *= 0.5;
	projection_coordinates += 0.5;
	
	//closest = LinearizeDepth(texture(shadow_map, projection_coordinates.xy).r);	//get the colour for the shadow off of the texture
	closest = texture(shadow_map, projection_coordinates.xy).r;
	
	current = projection_coordinates.z;
	
	return (((current - bias) > closest) ? 1.0f : 0.0f);
}
float shadowFactor;

vec2 location(vec4 lightspace_position_in)
{
	projection_coordinates = lightspace_position_in.xyz / lightspace_position_in.w;
	
	//ensures that the transformed value is within the [0,1] bracket of the shadow texture
	projection_coordinates *= 0.5;
	projection_coordinates += 0.5;
	
	return projection_coordinates.xy;	//get the colour for the shadow off of the texture
}

void main()
{
	//the normal of the surface is being interpolated, need to renormalise to ensure it is a unit normal
	norm = normalize(normal_vertex);
	//extract the position into a vec3 according to type of light
	if (position_light.w > 0.9)
	{
		//is a position
		position_light3 = vec3(position_light.x, position_light.y, position_light.z);
		//direction is the difference between the location and the interpolated vertex
		lightdir = normalize(position_vertex - position_light3);
	}
	else
	{
		//is a vector, but we still need a position, so take this as the arbitrary position
		position_light3 = vec3(position_light3.xyz);
		//the direction is simply the normalised version of the passed in vector
		lightdir = normalize(vec3(-1.0f * position_light.x, -1.0f * position_light.y, -1.0f * position_light.z));
	}
	//add the colour to the ambient lighting
	ambient = ambient_light * colour_light;
	
	//calculate the diffuse lighting effects
	diff	 = max ( dot(normal_vertex, lightdir), 0);
	diffuse  = diff * colour_light * diffuse_light;
	
	//calculate the specular lighting effects
	viewdir		= normalize(position_vertex - camera_position);
	reflectdir	= reflect(-1.0*lightdir, norm);
	spec		= pow( max( dot(viewdir, reflectdir), 0.0), 64);
	specular	= specular_light * spec * colour_light;
	
	
	if (position_light.w > 0.9f)
	{
		//point light, attenuate
		distance = length (position_light3 - position_vertex);
		attn = 1.0f / (attenuation_constants.x + (attenuation_constants.y * distance) + (attenuation_constants.z * distance * distance));
		ambient  *= attn;
		diffuse  *= attn;
		specular *= attn;
	}
	bias = max(shadow_bias * (1.0 - dot(norm, lightdir)), shadow_bias/10);
	shadowFactor = 1.0 - generateShadows(lightspace_position,bias);
	
	//toggles the shadows being applied to
	if (disable_shadows)
	{
		colour = vec4((ambient + diffuse + specular) * colour_vertex, 1.0f);
	}
	else
	{
		colour = vec4((ambient + (diffuse + specular) * shadowFactor) * colour_vertex , 1.0f);
	}
	
}