#version 330

uniform sampler2D texture;
uniform vec3 LightPosition;
uniform vec3 LightColor;
uniform vec3 CameraPosition;
//uniform vec2 phong;

in vec3 rgb;
in vec2 TextureColor;
in vec3 PixelNormal;
in vec3 PixelPosition;

out vec4 FragColor;

void main() {
	// Ambient component - 	ambiental = 10 % * LightColor;
	vec3 ambiental = 0.1f * LightColor;

	// Diffuse component - 	difusse = normalize(Light) * normalize(PixelNormal);
	vec3 L = normalize(LightPosition - PixelPosition);
	vec3 N = normalize(PixelNormal);
	vec3 diffuse = max(dot(N, L), 0.0f) * normalize(LightColor);

	// Specular component -	CamaraPosition = cos(R, V) *  LightColor;
	vec3 R = reflect(-L, PixelNormal);
	vec3 V = normalize(CameraPosition - PixelPosition);
	vec3 specular = 0.5 * pow(dot(V, R), 32) * LightColor;
	
	vec3 phong = ambiental + diffuse + specular;

	FragColor = texture2D(texture, TextureColor) * vec4(phong, 1.0f);

	// FragColor = texture2D(texture, TextureColor);
}