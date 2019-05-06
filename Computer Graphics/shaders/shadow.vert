#version 330

in vec3 VertexPosition;
in vec3 InterpolatedColor;
in vec3 VertexNormal;
in vec2 TexturePosition;

out vec3 rgb;
out vec3 IterpolatedVertexNormal;
out vec3 PixelPosition;
out vec2 TextureColor;
out vec4 PixelPositionLightSpace;

uniform mat4 mxpMatrix;
uniform mat4 modelMatrix;
uniform mat4 LightVPMatrix;

void main()
{
	rgb = InterpolatedColor;
	PixelPosition = vec3(modelMatrix*vec4(VertexPosition, 1.0f));

	IterpolatedVertexNormal = VertexNormal;
	TextureColor = TexturePosition;

	PixelPositionLightSpace = LightVPMatrix * vec4(PixelPosition, 1.0f);

	gl_Position = mxpMatrix * vec4(VertexPosition, 1.0f);
}