#version 330

uniform sampler2D text1;
uniform sampler2D text2;
//uniform vec2 phong;

in vec3 rgb;
in vec2 TextureColor;

out vec4 FragColor;

void main() {
	vec4 x = texture2D(text1, TextureColor);
	vec4 y = texture2D(text2, TextureColor);
	FragColor =  mix(x, y, 0.2);
	//FragColor = vec4(phong, 1.0);
}