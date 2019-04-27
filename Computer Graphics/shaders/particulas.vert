#version 330

in vec2 TexturePosition;
in vec3 VertexPosition;
in vec3 InterpolatedColor;

out vec2 TextureColor;
out vec3 rgb;

uniform vec3 newPosition;
uniform mat4 mModelo;
uniform mat4 mVista;
uniform mat4 mProyeccion;

// uniform mat4 mxpMatrix;


void main()
{
	rgb = InterpolatedColor;
	float x = VertexPosition.x + newPosition.x;
	float y = VertexPosition.y + newPosition.y;
	//Billboard - remove float z = VertexPosition.z  + newPosition.z;
	float z = VertexPosition.z;
	// mxpMatrix = Projection * View * Model;
	gl_Position = mProyeccion *  mVista * mModelo * vec4(vec3(x,y,z), 1.0f);

	TextureColor = TexturePosition;
}
