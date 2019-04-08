#version 330

// in vec3 color;

in vec3 rgb;
out vec4 FragColor;
uniform vec2 iResolution;

void main() {

	vec2 uv = (gl_FragCoord.xy) / iResolution;

	if(distance(vec3(uv, 0), vec3(0.5, 0.5, 0)) < 0.25)
		discard;

	FragColor = vec4(rgb, 1.0f);
}
