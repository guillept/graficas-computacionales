#version 330

in vec2 TexturePosition;
in vec3 VertexPosition;
in vec3 InterpolatedColor;

out vec2 TextureColor;
out vec3 rgb;
out vec3 PixelNormal;
out vec3 PixelPosition;

uniform vec3 newPosition;
uniform mat4 mModelo;
uniform mat4 mVista;
uniform mat4 mProyeccion;
uniform mat4 mxpMatrix;


void main()
{
	mat3 NormalMatrix = transpose(inverse(mat3(modelMatrix)));
	
	PixelNormal = NormalMatrix * VertexNormal;
	PixelPosition = vec3(modelMatrix * vec4(VertexPosition, 1.0f));
	
	rgb = InterpolatedColor;
	gl_Position = mxpMatrix * vec4(VertexPosition, 1.0f);
	TextureColor = TexturePosition;
}
