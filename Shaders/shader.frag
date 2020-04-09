#version 330											

in vec2 TexCoord;										

out vec4 colour;

struct DirectionalLight
{
	vec3 colour;
	float intensity;
};

uniform sampler2D Texture;
uniform DirectionalLight directionalLight;

void main()
{	
	vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.intensity;

	colour = texture(Texture, TexCoord) * ambientColour;		
}