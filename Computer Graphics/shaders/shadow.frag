#version 330

uniform sampler2D texture;
uniform sampler2D DepthMap;
uniform vec3 LightPosition;
uniform vec3 LightColor;
uniform vec3 CameraPosition;

in vec3 rgb;
in vec2 TextureColor;
in vec3 PixelNormal;
in vec3 PixelPosition;
in vec4 PixelPositionLightSpace;

out vec4 FragColor;


float IsPixelOccluded(vec4 pixelPositionLightSpace)
{
	// Convertir pixelPositionLightSpace a Normalized Device Space [-1, 1] 
	vec3 projCoords = pixelPositionLightSpace.xyz / pixelPositionLightSpace.w;

	// Transformar el resultado anterior al rango [0, 1]. Almacenarlo en una variable de nombre projCoords.
	projCoords = projCoords * 0.5f + 0.5f;

	// Muestrear el canal rojo del mapa de profundidad (textura _depthmap la clase depth_buffer) usando projCoords.xy como coordenadas de textura. Con esto obtenemos la profundidad del pixel en el primer render (desde la luz). Almacenar el resultado en una variable de nombre closestDepth.
	float closestDepth = texture2D(DepthMap, projCoords.xy).r;

	// La profundidad real del pixel (ya transformado) está en projCoords.z, currentDepth.
	float currentDepth = projCoords.z;

	// Si (currentDepth - 0.005) > closestDepth, regresar 1.0, de lo contrario, regresar 0.0.
	float shadow = currentDepth - 0.005f > closestDepth ? 1.0f : 0.0f;
	return shadow;
}

void main() {
	// Ambient component - 	ambiental = 10 % * LightColor;
	vec3 ambiental = 0.1f * LightColor;

	// Diffuse component - 	difusse = normalize(Light) * normalize(PixelNormal);
	vec3 L = normalize(LightPosition - PixelPosition);
	vec3 N = normalize(PixelNormal);
	vec3 diffuse = max(dot(N, L), 0.0f) * LightColor;

	// Specular component -	CamaraPosition = cos(R, V) *  LightColor;
	vec3 R = reflect(-L, PixelNormal);
	vec3 V = normalize(CameraPosition - PixelPosition);
	vec3 specular = 0.5 * pow(max(dot(V, R), 0.0f), 32) * LightColor;

	float shadow = IsPixelOccluded(PixelPositionLightSpace);
	vec3 phong = ambiental + (1.0f - shadow) * (diffuse + specular);
	
	// vec3 phong = ambiental + diffuse + specular;

	FragColor = texture2D(texture, TextureColor) * vec4(phong, 1.0f);

	// FragColor = texture2D(texture, TextureColor);
}