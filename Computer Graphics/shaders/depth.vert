#version 330

in vec2 Texture;
in vec3 VertexPosition ;
uniform mat4 mxpMatrix ;

out vec2 TextureColor;

void main ()
{

	TextureColor = Texture;
	gl_Position = mxpMatrix * vec4(VertexPosition , 1.0f);
}