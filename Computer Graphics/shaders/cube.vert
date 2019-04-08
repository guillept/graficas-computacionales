#version 330

in vec3 VertexPosition;
uniform mat4 mxpMatrix;
in vec3 InterpolatedColor;
out vec3 rgb;

void main()
{
	rgb = InterpolatedColor;
	gl_Position = mxpMatrix * vec4(VertexPosition, 1.0);

}