#include "scene_cube.h"

#include "ifile.h"
#include "time.h"

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

scene_cube::~scene_cube()
{
	// Borramos la memoria del ejecutable cuando la escena deja de existir.
	glDeleteProgram(shader_program_depth);
	glDeleteProgram(shader_program_shadow);
	glDeleteProgram(shader_program_floor);
}

void scene_cube::init()
{
	//Matriz de modelo translation*rotation*scale
	scale = scaleM();
	trans = translation();
	cgmath::mat4 matrizDeCamara = camera(cgmath::vec3(0,0,30.));
	View = cgmath::mat4::inverse(matrizDeCamara);
	Projection = projection();

	cgmath::mat4 camaraLuz = camera(cgmath::vec3(0, 15., 30.));
	ViewLuz = cgmath::mat4::inverse(camaraLuz);
	OrtoProj = ortographicProjection();
	LightVPMatrix = ViewLuz * OrtoProj;

	createCube();

	std::vector<unsigned int> indices =
	{
		0, 1, 2, 2, 3, 0, //Front
		4, 5, 6, 6, 7, 4, //Right
		11, 10, 9, 9, 8, 11, //Back
		14, 13, 12, 12, 15, 14, //Left
		16, 17, 18, 18, 19, 16, //Top
		20, 21, 22, 22, 23, 20,//Bottom
	};

	setColors();
	createTexturas();

	createNormales();

	createFloor();

	std::vector<unsigned int> indicesFloor =
	{
		0, 1, 2, 2, 3, 0, //Front
	};

	// Creacion y activacion del vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Creacion y configuracion del buffer del atributo de posicion
	glGenBuffers(1, &positionsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec3) * positions.size(), positions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind

	// A diferencia de los buffers de atributos, los buffers de indices deben permanecer activos. No hacemos unbind.
	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

	// Creacion y configuracion del buffer del atributo de color
	glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Creacion y configuracion del buffer del atributo de textura
	glGenBuffers(1, &texturasVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texturasVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * textura.size(), textura.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Creacion y configuracion del buffer del atributo de las normales
	glGenBuffers(1, &normalsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); //unbind vao

	// Creacion y activacion del vao
	glGenVertexArrays(1, &vaoFloor);
	glBindVertexArray(vaoFloor);

	// Creacion y configuracion del buffer del atributo de posicion
	glGenBuffers(1, &floorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec3) * floor.size(), floor.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind

	// A diferencia de los buffers de atributos, los buffers de indices deben permanecer activos. No hacemos unbind.
	glGenBuffers(1, &indicesFloorBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesFloorBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicesFloor.size(), indicesFloor.data(), GL_STATIC_DRAW);


	// Creacion y configuracion del buffer del atributo de textura
	glGenBuffers(1, &texturasFloorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texturasFloorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * texturaFloor.size(), texturaFloor.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); //unbind vao
	
	//Caja
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	ilLoadImage("images/crate.png");
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //minificacion
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //magnificacion
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Coordenda S
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Coordenada T

	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT),
		ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0,
		ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData()); //IL_IMAGE_TYPE

	ilBindImage(0);
	ilDeleteImages(1, &imageID);

	//Floor
	ilGenImages(1, &floorId);
	ilBindImage(floorId);
	ilLoadImage("images/floor.jpg");
	glGenTextures(1, &textureFloorId);
	glBindTexture(GL_TEXTURE_2D, textureFloorId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //minificacion
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //magnificacion
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Coordenda S
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Coordenada T

	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT),
		ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0,
		ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData()); //IL_IMAGE_TYPE

	ilBindImage(0);
	ilDeleteImages(1, &floorId);

	//Creación del buffer de profundidad
	depthBuffer.create(2048);

	ifile shader_file;
	shader_file.read("shaders/depth.vert");
	std::string vertex_source = shader_file.get_contents();
	const GLchar* vertex_source_c = (const GLchar*)vertex_source.c_str();
	GLuint depth_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(depth_vertex_shader, 1, &vertex_source_c, nullptr);
	glCompileShader(depth_vertex_shader);

	// Revision de errores de compilacion del vertex shader
	GLint depth_vertex_compiled;
	glGetShaderiv(depth_vertex_shader, GL_COMPILE_STATUS, &depth_vertex_compiled);
	if (depth_vertex_compiled != GL_TRUE)
	{
		GLint log_length;
		glGetShaderiv(depth_vertex_shader, GL_INFO_LOG_LENGTH, &log_length);

		std::vector<GLchar> log;
		log.resize(log_length);
		glGetShaderInfoLog(depth_vertex_shader, log_length, &log_length, &log[0]);
		std::cout << "Syntax errors in vertex shader: " << std::endl;
		for (auto& c : log) std::cout << c;
		std::cout << std::endl;
	}

	shader_file.read("shaders/depth.frag");
	std::string fragment_source = shader_file.get_contents();
	const GLchar* fragment_source_c = (const GLchar*)fragment_source.c_str();
	GLuint depth_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(depth_fragment_shader, 1, &fragment_source_c, nullptr);
	glCompileShader(depth_fragment_shader);

	// Revision de errores de compilacion del fragment shader
	GLint depth_fragment_compiled;
	glGetShaderiv(depth_fragment_shader, GL_COMPILE_STATUS, &depth_fragment_compiled);
	if (depth_fragment_compiled != GL_TRUE)
	{
		GLint log_length;
		glGetShaderiv(depth_fragment_shader, GL_INFO_LOG_LENGTH, &log_length);

		std::vector<GLchar> log;
		log.resize(log_length);
		glGetShaderInfoLog(depth_fragment_shader, log_length, &log_length, &log[0]);
		std::cout << "Syntax errors in fragment shader: " << std::endl;
		for (auto& c : log) std::cout << c;
		std::cout << std::endl;
	}

	//------------------------------------------------
	//Shadow Shaders
	shader_file.read("shaders/shadow.vert");
	vertex_source = shader_file.get_contents();
	vertex_source_c = (const GLchar*)vertex_source.c_str();
	GLuint shadow_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shadow_vertex_shader, 1, &vertex_source_c, nullptr);
	glCompileShader(shadow_vertex_shader);

	// Revision de errores de compilacion del vertex shader
	GLint shadow_vertex_compiled;
	glGetShaderiv(shadow_vertex_shader, GL_COMPILE_STATUS, &shadow_vertex_compiled);
	if (shadow_vertex_compiled != GL_TRUE)
	{
		GLint log_length;
		glGetShaderiv(shadow_vertex_shader, GL_INFO_LOG_LENGTH, &log_length);

		std::vector<GLchar> log;
		log.resize(log_length);
		glGetShaderInfoLog(shadow_vertex_shader, log_length, &log_length, &log[0]);
		std::cout << "Syntax errors in vertex shader: " << std::endl;
		for (auto& c : log) std::cout << c;
		std::cout << std::endl;
	}

	shader_file.read("shaders/shadow.frag");
	vertex_source = shader_file.get_contents();
	fragment_source_c = (const GLchar*)vertex_source.c_str();
	GLuint shadow_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shadow_fragment_shader, 1, &fragment_source_c, nullptr);
	glCompileShader(shadow_fragment_shader);
	// Revision de errores de compilacion del fragment shader
	GLint shadow_fragment_compiled;
	glGetShaderiv(shadow_fragment_shader, GL_COMPILE_STATUS, &shadow_fragment_compiled);
	if (shadow_fragment_compiled != GL_TRUE)
	{
		GLint log_length;
		glGetShaderiv(shadow_fragment_shader, GL_INFO_LOG_LENGTH, &log_length);

		std::vector<GLchar> log;
		log.resize(log_length);
		glGetShaderInfoLog(shadow_fragment_shader, log_length, &log_length, &log[0]);
		std::cout << "Syntax errors in fragment shader: " << std::endl;
		for (auto& c : log) std::cout << c;
		std::cout << std::endl;
	}

	//-------------------------------------------------------------------
	shader_file.read("shaders/floor.vert");
	vertex_source = shader_file.get_contents();
	vertex_source_c = (const GLchar*)vertex_source.c_str();
	GLuint floor_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(floor_vertex_shader, 1, &vertex_source_c, nullptr);
	glCompileShader(floor_vertex_shader);

	// Revision de errores de compilacion del vertex shader
	GLint floor_vertex_compiled;
	glGetShaderiv(floor_vertex_shader, GL_COMPILE_STATUS, &floor_vertex_compiled);
	if (floor_vertex_compiled != GL_TRUE)
	{
		GLint log_length;
		glGetShaderiv(floor_vertex_shader, GL_INFO_LOG_LENGTH, &log_length);

		std::vector<GLchar> log;
		log.resize(log_length);
		glGetShaderInfoLog(floor_vertex_shader, log_length, &log_length, &log[0]);
		std::cout << "Syntax errors in vertex shader: " << std::endl;
		for (auto& c : log) std::cout << c;
		std::cout << std::endl;
	}

	shader_file.read("shaders/floor.frag");
	vertex_source = shader_file.get_contents();
	fragment_source_c = (const GLchar*)vertex_source.c_str();
	GLuint floor_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(floor_fragment_shader, 1, &fragment_source_c, nullptr);
	glCompileShader(floor_fragment_shader);
	// Revision de errores de compilacion del fragment shader
	GLint floor_fragment_compiled;
	glGetShaderiv(floor_fragment_shader, GL_COMPILE_STATUS, &floor_fragment_compiled);
	if (floor_fragment_compiled != GL_TRUE)
	{
		GLint log_length;
		glGetShaderiv(floor_fragment_shader, GL_INFO_LOG_LENGTH, &log_length);

		std::vector<GLchar> log;
		log.resize(log_length);
		glGetShaderInfoLog(floor_fragment_shader, log_length, &log_length, &log[0]);
		std::cout << "Syntax errors in fragment shader: " << std::endl;
		for (auto& c : log) std::cout << c;
		std::cout << std::endl;
	}


	//--------------------------------------------------------------------

	//Depth Shader
	shader_program_depth = glCreateProgram();
	glAttachShader(shader_program_depth, depth_vertex_shader);
	glAttachShader(shader_program_depth, depth_fragment_shader);

	// Asignar Buffer a variables de IN en VertexShader
	glBindAttribLocation(shader_program_depth, 0, "VertexPosition");
	glLinkProgram(shader_program_depth);

	// Borramos los shaders, porque ya tenemos el ejecutable
	glDeleteShader(depth_vertex_shader);
	glDeleteShader(depth_fragment_shader);

	glUseProgram(shader_program_depth);

	//-----------------------------------------------------------------------
	// Shadow
	shader_program_shadow = glCreateProgram();
	glAttachShader(shader_program_shadow, shadow_vertex_shader);
	glAttachShader(shader_program_shadow, shadow_fragment_shader);

	// Asignar Buffer a variables de IN en VertexShader
	glBindAttribLocation(shader_program_shadow, 0, "VertexPosition");
	glBindAttribLocation(shader_program_shadow, 1, "InterpolatedColor");
	glBindAttribLocation(shader_program_shadow, 2, "TexturePosition");
	glBindAttribLocation(shader_program_shadow, 3, "VertexNormal");
	glLinkProgram(shader_program_shadow);

	// Borramos los shaders, porque ya tenemos el ejecutable
	glDeleteShader(shadow_vertex_shader);
	glDeleteShader(shadow_fragment_shader);

	glUseProgram(shader_program_shadow);

	// cgmath::vec3 LightColor = cgmath::vec3(1.0f, 1.0f, 1.0f); //uniform
	GLuint lightcolor_location = glGetUniformLocation(shader_program_shadow, "LightColor");
	glUniform3f(lightcolor_location, 1.0f, 1.0f, 1.0f);

	//cgmath::vec3 LightPosition = cgmath::vec3(1.0f, 1.0f, 1.0f); //uniform
	GLuint lightpos_location = glGetUniformLocation(shader_program_shadow, "LightPosition");
	glUniform3f(lightpos_location, 0.0f, 0.0f, 10.0f);

	GLuint campos_location = glGetUniformLocation(shader_program_shadow, "CameraPosition");
	glUniform3f(campos_location, 0.0f, 0.0f, 10.0f);
	
	GLuint texture1_location = glGetUniformLocation(shader_program_shadow, "texture");
	glUniform1i(texture1_location, 0);

	GLuint texture1_location_depthmap = glGetUniformLocation(shader_program_shadow, "DepthMap");
	glUniform1i(texture1_location_depthmap, 1);

	//-------------------------------------------------------
	//Floor

	shader_program_floor = glCreateProgram();
	glAttachShader(shader_program_floor, floor_vertex_shader);
	glAttachShader(shader_program_floor, floor_fragment_shader);

	// Asignar Buffer a variables de IN en VertexShader
	glBindAttribLocation(shader_program_floor, 0, "VertexPosition");
	glBindAttribLocation(shader_program_floor, 1, "TexturePosition");
	glLinkProgram(shader_program_floor);

	// Borramos los shaders, porque ya tenemos el ejecutable
	glDeleteShader(floor_vertex_shader);
	glDeleteShader(floor_fragment_shader);

	glUseProgram(shader_program_floor);

	glUseProgram(0);


}

void scene_cube::awake()
{
	glClearColor(1.0f, 0.913f, 0.301f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void scene_cube::sleep()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_PROGRAM_POINT_SIZE);
}

void scene_cube::first_render() {
	
	// Activar el framebuffer personalizado. Limpiar los buffers de profundidad y color.
	depthBuffer.bind();
	
	// Limpiar los buffers de profundidad y color.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader_program_depth);
	ModelFloor = scale * trans;
	mxpFloorMatrix = Projection * View * ModelFloor;

	GLuint mxpMatrix_location_floor = glGetUniformLocation(shader_program_depth, "mxpMatrix");
	glUniformMatrix4fv(mxpMatrix_location_floor, 1, GL_FALSE, &mxpFloorMatrix[0][0]);

	/*glActiveTexture(GL_TEXTURE0); // Se posicionan en el bucket 0
	glBindTexture(GL_TEXTURE_2D, textureFloorId); // Activan la textura en ese bucket*/

	glBindVertexArray(vaoFloor);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); //gl_trinagle_strip
	glBindVertexArray(0);

	// Desactivar los  shaders y las texturas.
	/*glActiveTexture(GL_TEXTURE0); // Posicionarse en el bucket 0
	glBindTexture(GL_TEXTURE_2D, 0); // Desactivan la textura*/

	glUseProgram(0);

	// Activar los shaders Depth.vert y Depth.frag
	glUseProgram(shader_program_depth);

	// Configurar la matriz mvp para cada geometría y renderear la escena.
	GLuint mxpMatrix_location = glGetUniformLocation(shader_program_depth, "mxpMatrix");
	glUniformMatrix4fv(mxpMatrix_location, 1, GL_FALSE, &mxpMatrix[0][0]);
	
	//vista y proyeccion de la luz
	GLuint lightmvp_location = glGetUniformLocation(shader_program_shadow, "LightVPMatrix");
	glUniformMatrix4fv(lightmvp_location, 1, GL_FALSE, &LightVPMatrix[0][0]);

	GLuint model_location = glGetUniformLocation(shader_program_shadow, "modelMatrix");
	glUniformMatrix4fv(model_location, 1, GL_FALSE, &Model[0][0]);
	
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, nullptr); //gl_trinagle_strip
	glBindVertexArray(0);

	// Desactivar los shaders Depth.vert y Depth.frag
	glUseProgram(0);
	//Unbind depth
	// Desactivar el framebuffer personalizado. Regresar el viewport al tamaño de la ventana.
	depthBuffer.unbind();
	glViewport(0, 0, 400, 400);
}

void scene_cube::second_render() {

	// Limpiar los buffers de profundidad y color.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader_program_depth);
	ModelFloor = scale * trans;
	mxpFloorMatrix = Projection * View * ModelFloor;

	GLuint mxpMatrix_location_floor = glGetUniformLocation(shader_program_depth, "mxpMatrix");
	glUniformMatrix4fv(mxpMatrix_location_floor, 1, GL_FALSE, &mxpFloorMatrix[0][0]);

	/*glActiveTexture(GL_TEXTURE0); // Se posicionan en el bucket 0
	glBindTexture(GL_TEXTURE_2D, textureFloorId); // Activan la textura en ese bucket*/

	glBindVertexArray(vaoFloor);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); //gl_trinagle_strip
	glBindVertexArray(0);

	// Desactivar los  shaders y las texturas.
	/*glActiveTexture(GL_TEXTURE0); // Posicionarse en el bucket 0
	glBindTexture(GL_TEXTURE_2D, 0); // Desactivan la textura*/

	glUseProgram(0);

	// Activar los shaders shaders de dibujado sombras Shadow.vert y Shadow.frag
	glUseProgram(shader_program_shadow);
	// Configurar todos los uniforms y matrices necesarios para phong shading. - init
	// Enviar la matriz de vista. Enviar la matriz de vista-proyección de la cámara en posición luz.
	// Hacer bind del mapa de profundidad y las texturas cada geometría. 
	GLuint mxpMatrix_location = glGetUniformLocation(shader_program_shadow, "mxpMatrix");
	glUniformMatrix4fv(mxpMatrix_location, 1, GL_FALSE, &mxpMatrix[0][0]);

	GLuint lightmvp_location = glGetUniformLocation(shader_program_shadow, "LightVPMatrix");
	glUniformMatrix4fv(lightmvp_location, 1, GL_FALSE, &LightVPMatrix[0][0]);

	GLuint model_location = glGetUniformLocation(shader_program_shadow, "modelMatrix");
	glUniformMatrix4fv(model_location, 1, GL_FALSE, &Model[0][0]);

	glActiveTexture(GL_TEXTURE0); // Se posicionan en el bucket 0
	glBindTexture(GL_TEXTURE_2D, textureId); // Activan la textura en ese bucket

	glActiveTexture(GL_TEXTURE1);
	depthBuffer.bindDepthMap();


	// Renderear la escena
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, nullptr); //gl_trinagle_strip
	glBindVertexArray(0);

	// Desactivar los  shaders y las texturas.
	glActiveTexture(GL_TEXTURE0); // Posicionarse en el bucket 0
	glBindTexture(GL_TEXTURE_2D, 0); // Desactivan la textura

	glActiveTexture(GL_TEXTURE1);
	depthBuffer.unbindDepthMap();
	glBindTexture(GL_TEXTURE_2D, 0); // Desactivan la textura

	glUseProgram(0);
}

void scene_cube::mainLoop()
{

	float iTime = time::elapsed_time().count();

	rotZ = rotateZ(iTime);
	rotY = rotateY(iTime);
	rotX = rotateX(iTime);

	Model = rotX * rotY * rotZ * scale * trans;
	mxpMatrix = Projection * View * Model;

	//Bind depth
	first_render();

	//Bind shadow
	second_render();
}

void scene_cube::resize(int width, int height)
{
	//Inicio, Fin (coordenadas)
	glViewport(0, 0, width, height);

	aspect = width / height;
}

float scene_cube::radians(float grados) {
	return (grados * M_PI) / 180.;
}

cgmath::mat4 scene_cube::rotateX(float iTime)
{
	return cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., cos(radians(30.)*iTime), sin(radians(30.)*iTime), 0.),
		cgmath::vec4(0., -sin(radians(30.)*iTime), cos(radians(30.)*iTime), 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);
}

cgmath::mat4 scene_cube::rotateY(float iTime)
{
	return cgmath::mat4(
		cgmath::vec4(cos(radians(60.)*iTime), 0., -sin(radians(60.)*iTime), 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(sin(radians(60.)*iTime), 0., cos(radians(60.)*iTime), 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);
}

cgmath::mat4 scene_cube::rotateZ(float iTime)
{
	return  cgmath::mat4(
		cgmath::vec4(cos(radians(30.)*iTime), sin(radians(30.)*iTime), 0., 0.),
		cgmath::vec4(-sin(radians(30.)*iTime), cos(radians(30.)*iTime), 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);
}

cgmath::mat4 scene_cube::scaleM()
{
	return cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);
}

cgmath::mat4 scene_cube::translation()
{
	return cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);
}

cgmath::mat4 scene_cube::camera(cgmath::vec3 camara)
{
	return cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(camara.x, camara.y, camara.z, 1.)
	);

}

cgmath::mat4 scene_cube::projection()
{
	float Near = 1.0f;
	float Far = 1000.f;
	float fov = radians(60.);

	return cgmath::mat4(
		cgmath::vec4(1. / (aspect*tan(fov / 2.)), 0., 0., 0.),
		cgmath::vec4(0., 1. / (tan(fov / 2.)), 0., 0.),
		cgmath::vec4(0., 0., -((Far + Near) / (Far - Near)), -1.),
		cgmath::vec4(0., 0., -((2 * Far*Near) / (Far - Near)), 1.)
	);
}

cgmath::mat4 scene_cube::ortographicProjection()
{
	float Near = 1.0f;
	float Far = 1000.f;
	float right = 100.5f; //entre mas grande mas cerca
	float left = -100.5f;
	float top = 100.5f;
	float bottom = -100.5f;

	return cgmath::mat4(
		cgmath::vec4(2. / (right - left), 0., 0., 0.),
		cgmath::vec4(0., 2. / (top - bottom), 0., 0.),
		cgmath::vec4(0., 0., -2 / (Far - Near),	0.),
		cgmath::vec4(-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((Far + Near) / (Far - Near)), 1.)
	);
}

void scene_cube::createCube()
{
	//Front
	positions.push_back(cgmath::vec3(-x, y, z)); //v1 - 0
	positions.push_back(cgmath::vec3(-x, -y, z)); //v2 - 1 
	positions.push_back(cgmath::vec3(x, -y, z)); //v3 - 2
	positions.push_back(cgmath::vec3(x, y, z)); //v4 - 3

	//Rigth
	positions.push_back(cgmath::vec3(x, y, z)); //v4 - 4
	positions.push_back(cgmath::vec3(x, -y, z)); //v3 - 5
	positions.push_back(cgmath::vec3(x, -y, -z)); //v7 - 6
	positions.push_back(cgmath::vec3(x, y, -z)); //v6 - 7

	//Back
	positions.push_back(cgmath::vec3(-x, y, -z)); //v5 - 8
	positions.push_back(cgmath::vec3(-x, -y, -z)); //v8 - 9
	positions.push_back(cgmath::vec3(x, -y, -z)); //v7 - 10
	positions.push_back(cgmath::vec3(x, y, -z)); //v6 - 11

	//Left
	positions.push_back(cgmath::vec3(-x, y, z)); //v1 - 12
	positions.push_back(cgmath::vec3(-x, -y, z)); //v2 - 13
	positions.push_back(cgmath::vec3(-x, -y, -z)); //v8 - 14
	positions.push_back(cgmath::vec3(-x, y, -z)); //v5 - 15

	//Top
	positions.push_back(cgmath::vec3(-x, y, -z)); //v5 - 16
	positions.push_back(cgmath::vec3(-x, y, z)); //v1 - 17
	positions.push_back(cgmath::vec3(x, y, z)); //v4 - 18
	positions.push_back(cgmath::vec3(x, y, -z)); //v6 - 19

	//Bottom
	positions.push_back(cgmath::vec3(-x, -y, z)); //v2 - 20
	positions.push_back(cgmath::vec3(x, -y, z)); //v3 - 21
	positions.push_back(cgmath::vec3(x, -y, -z)); //v7 - 22
	positions.push_back(cgmath::vec3(-x, -y, -z)); //v8 - 23

	//Floor
	positions.push_back(cgmath::vec3(-20, -y - 1, 50)); //v2 - 24
	positions.push_back(cgmath::vec3(20, -y - 1, 50)); //v3 - 25
	positions.push_back(cgmath::vec3(20, -y - 1, -50)); //v7 - 26
	positions.push_back(cgmath::vec3(-20, -y - 1, -50)); //v8 - 27
}

void scene_cube::setColors()
{
	for (int i = 0; i < minimoNumeroVertices; i++)
		colors.push_back(cgmath::vec3(1., 1., 1.)); //front
	for (int i = 0; i < minimoNumeroVertices; i++)
		colors.push_back(cgmath::vec3(1., 0.0, 0.0)); //right
	for (int i = 0; i < minimoNumeroVertices; i++)
		colors.push_back(cgmath::vec3(0.0, 1., 0.)); //back
	for (int i = 0; i < minimoNumeroVertices; i++)
		colors.push_back(cgmath::vec3(0.0, 0.0, 1.)); //left
	for (int i = 0; i < minimoNumeroVertices; i++)
		colors.push_back(cgmath::vec3(0.2, 0.2, 0.2)); //top
	for (int i = 0; i < minimoNumeroVertices; i++)
		colors.push_back(cgmath::vec3(0., 0., 0.)); //bottom
}

void scene_cube::createTexturas() 
{
	for (int i = 0; i < 6; i++)
	{
		textura.push_back(cgmath::vec2(1.0, 1.0));
		textura.push_back(cgmath::vec2(1.0, 0.0));
		textura.push_back(cgmath::vec2(0.0, 0.0));
		textura.push_back(cgmath::vec2(0.0, 1.0));
	}

	texturaFloor.push_back(cgmath::vec2(1.0, 1.0));
	texturaFloor.push_back(cgmath::vec2(1.0, 1.0));
	texturaFloor.push_back(cgmath::vec2(1.0, 1.0));
	texturaFloor.push_back(cgmath::vec2(1.0, 1.0));
}

void scene_cube::createNormales()
{
	normals.push_back(cgmath::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(cgmath::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(cgmath::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(cgmath::vec3(0.0f, 0.0f, 1.0f));

	normals.push_back(cgmath::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(cgmath::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(cgmath::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(cgmath::vec3(1.0f, 0.0f, 0.0f));

	normals.push_back(cgmath::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(cgmath::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(cgmath::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(cgmath::vec3(0.0f, 0.0f, -1.0f));

	normals.push_back(cgmath::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(cgmath::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(cgmath::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(cgmath::vec3(-1.0f, 0.0f, 0.0f));

	normals.push_back(cgmath::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(cgmath::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(cgmath::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(cgmath::vec3(0.0f, 1.0f, 0.0f));

	normals.push_back(cgmath::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(cgmath::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(cgmath::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(cgmath::vec3(0.0f, -1.0f, 0.0f));

}

void scene_cube::createFloor() {
	
	floor.push_back(cgmath::vec3(-xFloor, yFloor, -zFloor)); //v1 - 0
	floor.push_back(cgmath::vec3(-xFloor, -yFloor, -zFloor)); //v2 - 1 
	floor.push_back(cgmath::vec3(xFloor, -yFloor, -zFloor)); //v3 - 2
	floor.push_back(cgmath::vec3(xFloor, yFloor, -zFloor)); //v4 - 3
}