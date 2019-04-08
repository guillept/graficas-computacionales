#version 330

uniform mat4 mxpMatrix;

in vec2 TexturePosition;
in vec3 VertexPosition;
in vec3 InterpolatedColor;

out vec2 TextureColor;
out vec3 rgb;

void main()
{
	rgb = InterpolatedColor;
	gl_Position = mxpMatrix * vec4(VertexPosition, 1.0);
	TextureColor = TexturePosition;

}