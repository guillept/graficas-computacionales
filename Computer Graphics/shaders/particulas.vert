#version 330

in vec2 TexturePosition;
in vec3 VertexPosition;
in vec3 InterpolatedColor;

out vec2 TextureColor;
out vec3 rgb;

uniform vec3 newPosition;
// uniform mat4 mModelo;
// uniform mat4 mVista;
// uniform mat4 mProyeccion;
uniform mat4 mxpMatrix;


void main()
{
	rgb = InterpolatedColor;
	
	// mxpMatrix = Projection * View * Model;
	//  mProyeccion *  mVista * mModelo
	vec4 pos = mxpMatrix * vec4(newPosition, 1.0f);
	pos.x += VertexPosition.x;
	pos.y += VertexPosition.y;
	// pos.z += VertexPosition.z;
	//Billboard - remove float z = VertexPosition.z  + newPosition.z;

	gl_Position = pos;
	TextureColor = TexturePosition;
}
