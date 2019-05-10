#version 330

in vec3 VertexPosition ;
uniform mat4 mxpMatrix ;

void main ()
{
	gl_Position = mxpMatrix * vec4(VertexPosition , 1.0f);
}