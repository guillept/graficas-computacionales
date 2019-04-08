#version 330

in vec3 rgb;
out vec4 FragColor;

void main() {
	FragColor = vec4(rgb, 1.0f);
}