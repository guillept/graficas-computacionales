#version 330

uniform sampler2D text1;
uniform sampler2D text2;

out vec4 FragColor;

in vec2 TextureColor;

void main() {
	vec4 x = texture2D(text1, TextureColor);
	vec4 y = texture2D(text2, TextureColor);
	FragColor =  mix(x, y, 0.2);
}