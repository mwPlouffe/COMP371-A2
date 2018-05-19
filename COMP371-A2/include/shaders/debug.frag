#version 330 core
out vec4 colour;
in vec3 norm;
void main()
{
	colour = vec4(0.3 + norm.r, 0.7 + norm.g ,0.4 + norm.b, 1.0);
}