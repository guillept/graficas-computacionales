#version 330

uniform sampler2D texture;
//uniform vec2 phong;

in vec3 rgb;
in vec2 TextureColor;

out vec4 FragColor;

void main() {
	//FragColor = vec4(phong, 1.0);
	FragColor = texture2D(texture, TextureColor);
}