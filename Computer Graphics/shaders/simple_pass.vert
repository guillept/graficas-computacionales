#version 330

in vec3 VertexPositions;

void main() {

	gl_Position = vec4(VertexPositions, 1.0f);



}