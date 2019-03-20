#version 330

in vec3 VertexPositions;
in vec3 InterpolatedColor;
out vec3 rgb;

void main()
{
    // rgb = vec3(1.0, 0.5, 0.5);
	// color = vec3(0.423f, 0.653f, 0.423f);
	rgb = InterpolatedColor;
	gl_Position = vec4(VertexPositions, 1.0f);

}