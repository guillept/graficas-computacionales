#version 330

uniform mat4 mxpMatrix;

in vec2 TexturePosition;
in vec3 VertexPosition;

out vec2 TextureColor;

void main()
{
	gl_Position = mxpMatrix * vec4(VertexPosition, 1.0);
	TextureColor = TexturePosition;
}
