#version 330

in vec2 TexturePosition;
in vec3 VertexPosition;
in vec3 InterpolatedColor;
in vec3 VertexNormal;

out vec2 TextureColor;
out vec3 rgb;
out vec3 PixelNormal;
out vec3 PixelPosition;
out vec4 PixelPositionLightSpace;

uniform mat4 mxpMatrix;
uniform mat4 modelMatrix;
uniform mat4 LightVPMatrix;

void main()
{
	mat3 NormalMatrix = transpose(inverse(mat3(modelMatrix)));
	
	PixelNormal = NormalMatrix * VertexNormal;
	PixelPosition = vec3(modelMatrix * vec4(VertexPosition, 1.0f));
	
	rgb = InterpolatedColor;
	gl_Position = mxpMatrix * vec4(VertexPosition, 1.0f);
	TextureColor = TexturePosition;

	PixelPositionLightSpace=LightVPMatrix*vec4(PixelPosition, 1.0); 
}
