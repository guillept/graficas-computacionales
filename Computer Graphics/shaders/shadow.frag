#version 330

in vec3 InterpolatedColor;
in vec3 IterpolatedVertexNormal;
in vec3 PixelPosition;
in vec2 TextureColor;
in vec4 PixelPositionLightSpace;

out vec4 FragColor;

uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform mat4 modelMatrix;
uniform vec3 CamaraPosition;
uniform sampler2D text1;
uniform sampler2D ShadowMap;

float IsPixelOccluded(vec4 fragPosLightSpace)
{
	// Convertir pixelPositionLightSpace a Normalized Device Space [-1, 1] 
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

	// Transformar el resultado anterior al rango [0, 1]. Almacenarlo en una variable de nombre projCoords.
	projCoords = projCoords * 0.5f + 0.5f;

	// Muestrear el canal rojo del mapa de profundidad (textura _depthmap la clase depth_buffer) usando projCoords.xy como coordenadas de textura. Con esto obtenemos la profundidad del pixel en el primer render (desde la luz). Almacenar el resultado en una variable de nombre closestDepth.
	float closestDepth = texture2D(ShadowMap, projCoords.xy).r;

	// La profundidad real del pixel (ya transformado) está en projCoords.z, currentDepth.
	float currentDepth = projCoords.z;

	// Si (currentDepth - 0.005) > closestDepth, regresar 1.0, de lo contrario, regresar 0.0.
	float shadow = currentDepth - 0.005f > closestDepth ? 1.0f : 0.0f;
	return shadow;
}

void main()
{
	// Ambient component - 	ambiental = 10 % * LightColor;
	vec3 ambiental = 0.1f * LightColor;

	// Diffuse component - 	difusse = normalize(Light) * normalize(LightColor);
	vec3 L = normalize(LightPosition - PixelPosition);
	mat3 NormalMatrix = transpose(inverse(mat3(modelMatrix)));
	vec3 IterpolatedNormal = normalize(NormalMatrix * IterpolatedVertexNormal);
	vec3 diffuse = dot(normalize(IterpolatedNormal), L) * normalize(LightColor);

	// Specular component -	CamaraPosition = cos(R, V) *  LightColor;
	vec3 R = reflect(-L, IterpolatedNormal);
	vec3 V = normalize(CamaraPosition - PixelPosition);
	vec3 specular = 0.5 * pow(dot(V, R), 32) * LightColor;

	float shadow = IsPixelOccluded(PixelPositionLightSpace);
	
	vec3 phong = ambiental + (1.0f - shadow) * (diffuse + specular);
	
	FragColor = texture2D(text1, TextureColor) * vec4(phong, 1.0f);
}