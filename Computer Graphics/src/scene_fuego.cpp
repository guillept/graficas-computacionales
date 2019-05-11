#include "scene_fuego.h"
#include "ifile.h"

#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <algorithm>


scene_fuego::~scene_fuego()
{
	// Borramos la memoria del ejecutable cuando la escena deja de existir.
	glDeleteProgram(shader_program_depth);
	glDeleteProgram(shader_program_shadow);
}

void scene_fuego::init()
{
	//Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Projection = projection();
	trans = translation(0, 0., 100.f);

	cgmath::mat4 camaraLuz = camera(cgmath::vec3(0, 0., 80));
	ViewLuz = cgmath::mat4::inverse(camaraLuz);
	OrtoProj = ortographicProjection();
	LightVPMatrix = OrtoProj * ViewLuz;

	// Init Objects
	initParticulas();
	setTexturas();
	createNormales();
	createFloor();

	//Init Vaos
	createParticalesVao();

	//Creacion del buffer de profundidad
	depthBuffer.create(2048);

}

void scene_fuego::awake()
{
	glClearColor(0.f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void scene_fuego::sleep()
{
	glClearColor(0.f, 0.0f, 0.0f, 1.0f);
	glDisable(GL_PROGRAM_POINT_SIZE);
}

void scene_fuego::normalKeysDown(unsigned char key)
{
	//no tengo idea de porque se rotan al reves
	switch (key) {
	case 'a':
		moverCamara.z -= 1;
		break;
	case 'd':
		moverCamara.z += 1;
		break;
	case 'w':
		moverCamara.x -= 1;
		break;
	case 's':
		moverCamara.x += 1;
		break;
	case 'z':
		wind -= 0.05;
		break;
	case 'x':
		wind = 0;
		break;
	case 'c':
		wind += 0.05;
		break;
	}
}

void scene_fuego::resize(int width, int height)
{
	//Inicio, Fin (coordenadas)
	glViewport(0, 0, width, height);
	aspect = width / height;
}

void scene_fuego::mainLoop()
{
	// matrizDeCamara = rotz * rotY * rotx * scale * trans; 
	// rotY y scale se eliminan = identidad
	matrizDeCamara = rotateZ(moverCamara.z) * rotateX(moverCamara.x) * trans;
	View = cgmath::mat4::inverse(matrizDeCamara);

	std::sort(&particulas[0], &particulas[MAX_PARTICULAS - 1]);

	willPartiTheParticleLive = 0;
	for (int i = 0; i < MAX_PARTICULAS; i++)
	{
		index = particulas[i].position;

		//is particle alive?
		if (positions[index].z <= 5) {
			resetParticula(index);
		} else if (lifes[index] > 0) {
			lifes[index] -= 1.0;
			particulas[i].distance = calculateDistance(index);

			positions[index].x += veclocidad[index].x + wind;
			positions[index].y += veclocidad[index].y;
			positions[index].z += veclocidad[index].z;
			
			veclocidad[index].x = aceleracion[index].x * time::delta_time().count(); //Vf = a*t + Vo
			veclocidad[index].y = aceleracion[index].y * time::delta_time().count(); //Vf = a*t + Vo
			veclocidad[index].z = aceleracion[index].z * time::delta_time().count(); //Vf = a*t + Vo

		}
		//particle is dead
		else {
			willPartiTheParticleLive = random(1, 500);
			if (willPartiTheParticleLive >= 499) {
				resetParticula(index);
			}
		}
	}

	// Depth Render
	first_render();

	// Shadow Render
	second_render();
}

// DIBUJAR LA ESCENA

void scene_fuego::first_render() {

	// Activar el framebuffer personalizado. Limpiar los buffers de profundidad y color.
	depthBuffer.bind();

	// Limpiar los buffers de profundidad y color.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_program_depth);

	// Floor
	mxpFloorMatrix = OrtoProj * ViewLuz;

	// Enviar la matriz de vista. Enviar la matriz de vista-proyeccion de la camara en posicion luz.
	GLuint mxpMatrix_location_floor = glGetUniformLocation(shader_program_depth, "mxpMatrix");
	glUniformMatrix4fv(mxpMatrix_location_floor, 1, GL_FALSE, &mxpFloorMatrix[0][0]);

	//Renderear escena
	glBindVertexArray(vaoFloor);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); //gl_trinagle_strip
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0); // Se posicionan en el bucket 0
	glBindTexture(GL_TEXTURE_2D, textureId); // Activan la textura en ese bucket

	// Configurar la matriz mvp para cada geometria y renderear la escena.
	for (int i = 0; i < MAX_PARTICULAS; i++)
	{
		index = particulas[i].position;

		// Model = rotateX(0) * rotateY(0) * rotateZ(0) * scale * translation(positions[index].x, positions[index].y, positions[index].z);
		// rotX, rotY, rotZ y scale se eliminan = identidad
		Model = translation(positions[index].x, positions[index].y, positions[index].z); //identidad x,y,z -> posicion matricula

		// Particulas
		billboard(ViewLuz);
		mxpMatrix = OrtoProj * ViewModel;

		GLuint mxpMatrix_location = glGetUniformLocation(shader_program_depth, "mxpMatrix");
		glUniformMatrix4fv(mxpMatrix_location, 1, GL_FALSE, &mxpMatrix[0][0]);

		if (lifes[index] > 0) {
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	}

	glActiveTexture(GL_TEXTURE0); // Se posicionan en el bucket 0
	glBindTexture(GL_TEXTURE_2D, 0); // Desactivan la textura

	// Desactivar los shaders Depth.vert y Depth.frag
	glUseProgram(0);
	//Unbind depth
	// Desactivar el framebuffer personalizado. Regresar el viewport al tama�o de la ventana.
	depthBuffer.unbind();
	glViewport(0, 0, 400, 400);
}

void scene_fuego::second_render() {

	// Limpiar los buffers de profundidad y color.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activar los shaders shaders de dibujado sombras Shadow.vert y Shadow.frag
	glUseProgram(shader_program_shadow);
	ModelFloor = cgmath::mat4(1.0);
	mxpFloorMatrix = Projection * View;

	// Configurar todos los uniforms y matrices necesarios para phong shading. - init
	// Enviar la matriz de vista. Enviar la matriz de vista-proyeccion de la camara en posicion luz.
	// Hacer bind del mapa de profundidad y las texturas cada geometria. 
	GLuint mxpMatrix_location_ligth = glGetUniformLocation(shader_program_shadow, "mxpMatrix");
	glUniformMatrix4fv(mxpMatrix_location_ligth, 1, GL_FALSE, &mxpFloorMatrix[0][0]);

	GLuint lightmvp_location = glGetUniformLocation(shader_program_shadow, "LightVPMatrix");
	glUniformMatrix4fv(lightmvp_location, 1, GL_FALSE, &LightVPMatrix[0][0]);

	GLuint model_location_ligth = glGetUniformLocation(shader_program_shadow, "modelMatrix");
	glUniformMatrix4fv(model_location_ligth, 1, GL_FALSE, &ModelFloor[0][0]);

	glActiveTexture(GL_TEXTURE0); // Se posicionan en el bucket 0
	glBindTexture(GL_TEXTURE_2D, textureFloorId); // Activan la textura en ese bucket

	glActiveTexture(GL_TEXTURE1);
	depthBuffer.bindDepthMap();

	// Renderear la escena
	glBindVertexArray(vaoFloor);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); //gl_trinagle_strip
	glBindVertexArray(0);

	// Desactivar los  shaders y las texturas.
	glActiveTexture(GL_TEXTURE0); // Posicionarse en el bucket 0
	glBindTexture(GL_TEXTURE_2D, 0); // Desactivan la textura

	glActiveTexture(GL_TEXTURE1);
	depthBuffer.unbindDepthMap();

	// Particulas
	// Configurar todos los uniforms y matrices necesarios para phong shading. - init
	// Enviar la matriz de vista. Enviar la matriz de vista-proyeccion de la camara en posicion luz.

	// Hacer bind del mapa de profundidad y las texturas cada geometria. 
	glActiveTexture(GL_TEXTURE0); // Se posicionan en el bucket 0
	glBindTexture(GL_TEXTURE_2D, textureId); // Activan la textura en ese bucket

	glActiveTexture(GL_TEXTURE1);
	depthBuffer.bindDepthMap();

	//Renderear la escena
	for (int i = 0; i < MAX_PARTICULAS; i++)
	{
		index = particulas[i].position;

		// Model = rotateX(0) * rotateY(0) * rotateZ(0) * scale * translation(positions[index].x, positions[index].y, positions[index].z);
		// rotX, rotY, rotZ y scale se eliminan = identidad
		Model = translation(positions[index].x, positions[index].y, positions[index].z); //identidad x,y,z -> posicion matricula

		// Particulas
		billboard(View);
		mxpMatrix = Projection * ViewModel;

		GLuint mxpMatrix_location = glGetUniformLocation(shader_program_shadow, "mxpMatrix");
		glUniformMatrix4fv(mxpMatrix_location, 1, GL_FALSE, &mxpMatrix[0][0]);

		GLuint model_location = glGetUniformLocation(shader_program_shadow, "modelMatrix");
		glUniformMatrix4fv(model_location, 1, GL_FALSE, &Model[0][0]);

		if (lifes[index] > 0) {
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	}

	glActiveTexture(GL_TEXTURE0); // Se posicionan en el bucket 0
	glBindTexture(GL_TEXTURE_2D, 0); // Desactivan la textura

	glActiveTexture(GL_TEXTURE1);
	depthBuffer.unbindDepthMap();

	glUseProgram(0);

}

// OPERCIONES DE MATRICES

cgmath::mat4 scene_fuego::translation(GLfloat x, GLfloat y, GLfloat z)
{
	return cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(x, y, z, 1.)
	);
}

cgmath::mat4 scene_fuego::projection()
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

cgmath::mat4 scene_fuego::ortographicProjection()
{
	float Near = -80;
	float Far = 80.f;
	float right = 80.f; //entre mas grande mas cerca
	float left = -80.f;
	float top = 80.f;
	float bottom = -80.f;

	return cgmath::mat4(
		cgmath::vec4(2. / (right - left), 0., 0., 0.),
		cgmath::vec4(0., 2. / (top - bottom), 0., 0.),
		cgmath::vec4(0., 0., -2 / (Far - Near), 0.),
		cgmath::vec4(-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((Far + Near) / (Far - Near)), 1.)

	);
}

cgmath::mat4 scene_fuego::rotateX(GLfloat iTime)
{
	return cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., cos(radians(iTime)), sin(radians(iTime)), 0.),
		cgmath::vec4(0., -sin(radians(iTime)), cos(radians(iTime)), 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);
}

cgmath::mat4 scene_fuego::rotateY(GLfloat iTime)
{
	return cgmath::mat4(
		cgmath::vec4(cos(radians(iTime)), 0., -sin(radians(iTime)), 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(sin(radians(iTime)), 0., cos(radians(iTime)), 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);
}

cgmath::mat4 scene_fuego::rotateZ(GLfloat iTime)
{
	return  cgmath::mat4(
		cgmath::vec4(cos(radians(iTime)), sin(radians(iTime)), 0., 0.),
		cgmath::vec4(-sin(radians(iTime)), cos(radians(iTime)), 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);
}

void scene_fuego::billboard(cgmath::mat4 View)
{
	ViewModel = View * Model;

	// Column 0:
	ViewModel[0][0] = 1;
	ViewModel[0][1] = 0;
	ViewModel[0][2] = 0;

	// Column 1:
	ViewModel[1][0] = 0;
	ViewModel[1][1] = 1;
	ViewModel[1][2] = 0;

	// Column 2:
	ViewModel[2][0] = 0;
	ViewModel[2][1] = 0;
	ViewModel[2][2] = 1;
}

cgmath::mat4 scene_fuego::camera(cgmath::vec3 camara)
{
	return cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(camara.x, camara.y, camara.z, 1.)
	);

}

// CONTROLAR LAS PARTICULAS

void scene_fuego::createParticalesVao()
{
	std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 };

	// Creacion y activacion del vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindVertexArray(vao);

	// Creacion y configuracion del buffer del atributo de posicion
	glGenBuffers(1, &positionsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec3) * posicionesParticulaOrigen.size(), posicionesParticulaOrigen.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind

	// A diferencia de los buffers de atributos, los buffers de indices deben permanecer activos. No hacemos unbind.
	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

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

	//-----------------------------------------------------------------------
	//Floor

	std::vector<unsigned int> indicesFloor = { 0, 1, 2, 2, 3, 0 };
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
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Creacion y configuracion del buffer del atributo de textura
	glGenBuffers(1, &floorNormalsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, floorNormalsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * floorNormals.size(), floorNormals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); //unbind vao

	// Textura
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	ilLoadImage("images/fire.png");
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

	//Textura Floor
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

	//-----------------------------------------------------------------------
	//Depth Shader
	shader_program_depth = glCreateProgram();
	glAttachShader(shader_program_depth, depth_vertex_shader);
	glAttachShader(shader_program_depth, depth_fragment_shader);

	// Asignar Buffer a variables de IN en VertexShader
	glBindAttribLocation(shader_program_depth, 0, "VertexPosition");
	glBindAttribLocation(shader_program_depth, 2, "Texture");
	glLinkProgram(shader_program_depth);

	// Borramos los shaders, porque ya tenemos el ejecutable
	glDeleteShader(depth_vertex_shader);
	glDeleteShader(depth_fragment_shader);

	glUseProgram(shader_program_depth);

	//-----------------------------------------------------------------------
	// Shadow
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
	fragment_source = shader_file.get_contents();
	fragment_source_c = (const GLchar*)fragment_source.c_str();
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
	glDeleteShader(shader_program_shadow);
	glDeleteShader(shader_program_shadow);

	glUseProgram(shader_program_shadow);

	// cgmath::vec3 LightColor = cgmath::vec3(1.0f, 1.0f, 1.0f); //uniform
	GLuint lightcolor_location = glGetUniformLocation(shader_program_shadow, "LightColor");
	glUniform3f(lightcolor_location, 1.0f, 1.0f, 1.0f);

	//cgmath::vec3 LightPosition = cgmath::vec3(1.0f, 1.0f, 1.0f); //uniform
	GLuint lightpos_location = glGetUniformLocation(shader_program_shadow, "LightPosition");
	glUniform3f(lightpos_location, 0.0f, 0.0f, bound);


	GLuint campos_location = glGetUniformLocation(shader_program_shadow, "CameraPosition");
	glUniform3f(campos_location, 0.0f, 0.0f, bound);

	GLuint texture1_location = glGetUniformLocation(shader_program_shadow, "texture");
	glUniform1i(texture1_location, 0);

	GLuint texture1_location_depthmap = glGetUniformLocation(shader_program_shadow, "DepthMap");
	glUniform1i(texture1_location_depthmap, 1);

	glUseProgram(0);

}

void scene_fuego::createFloor() {

	floor.push_back(cgmath::vec3(-xFloor, yFloor, 0)); //v1 - 0
	floor.push_back(cgmath::vec3(-xFloor, -yFloor, 0)); //v2 - 1 
	floor.push_back(cgmath::vec3(xFloor, -yFloor, 0)); //v3 - 2
	floor.push_back(cgmath::vec3(xFloor, yFloor, 0)); //v4 - 3
}

void scene_fuego::initParticulas()
{
	//Front
	posicionesParticulaOrigen.push_back(cgmath::vec3(-1., 1., 0.)); //v1 - 0
	posicionesParticulaOrigen.push_back(cgmath::vec3(-1., -1., 0.)); //v2 - 1 
	posicionesParticulaOrigen.push_back(cgmath::vec3(1., -1., 0.)); //v3 - 2
	posicionesParticulaOrigen.push_back(cgmath::vec3(1., 1., 0.)); //v4 - 3

	for (int i = 0; i < MAX_PARTICULAS; i++)
	{
		//al particles are dead at the beginning
		lifes.push_back(0);

		//Particula struct
		particulas[i].position = i;
		particulas[i].distance = cgmath::vec3(0, 0, 0);

		setXYZ();
		positions.push_back(cgmath::vec4(x, y, z, 1.0f));
		veclocidad.push_back(cgmath::vec3(0, 0, 0));
		aceleracion.push_back(cgmath::vec3(0, 0, 0));
	}

	moverCamara = cgmath::vec3(0, 0, 0);
}

void scene_fuego::setTexturas() {

	for (int i = 0; i < 6; i++)
	{

		textura.push_back(cgmath::vec2(1.0, 1.0));
		textura.push_back(cgmath::vec2(1.0, 0.0));
		textura.push_back(cgmath::vec2(0.0, 0.0));
		textura.push_back(cgmath::vec2(0.0, 1.0));
	}

	texturaFloor.push_back(cgmath::vec2(1.0, 1.0));
	texturaFloor.push_back(cgmath::vec2(1.0, 0.0));
	texturaFloor.push_back(cgmath::vec2(0.0, 0.0));
	texturaFloor.push_back(cgmath::vec2(0.0, 1.0));
}

void scene_fuego::createNormales()
{
	//Front
	normals.push_back(cgmath::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(cgmath::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(cgmath::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(cgmath::vec3(0.0f, 0.0f, 1.0f));

	//Floor
	floorNormals.push_back(cgmath::vec3(0.0f, 0.0f, 1.0f));
	floorNormals.push_back(cgmath::vec3(0.0f, 0.0f, 1.0f));
	floorNormals.push_back(cgmath::vec3(0.0f, 0.0f, 1.0f));
	floorNormals.push_back(cgmath::vec3(0.0f, 0.0f, 1.0f));

}

void scene_fuego::resetParticula(int i)
{
	setXYZ();
	positions[i] = cgmath::vec4(x, y, z, 1.0f);
	veclocidad[i] = cgmath::vec3(0, 0, 0);
	lifes[i] = lifeTime;
	aceleracion[index].x = random(-maxAceleracion, maxAceleracion);
	aceleracion[index].y = random(gravedad, gravedad * 3);
	aceleracion[index].z = random(-maxAceleracion, maxAceleracion);
}

// OPERACIONES MATEMÁTICAS

GLfloat scene_fuego::radians(GLfloat grados) {
	return (grados * M_PI) / 180.;
}

GLfloat scene_fuego::random(GLfloat fMin, GLfloat fMax) {
	return fMin + (rand() / (RAND_MAX / (fMax - fMin)));
}

cgmath::vec3 scene_fuego::calculateDistance(int i)
{
	// Column 3
	cgmath::vec3 camara = cgmath::vec3(matrizDeCamara[3][0], matrizDeCamara[3][1], matrizDeCamara[3][2]);
	cgmath::vec3 position_particula = cgmath::vec3(positions[i].x, positions[i].y, positions[i].z);
	return camara - position_particula;
}

// FUNCIONES AUXILIARES

void scene_fuego::setXYZ()
{
	x = random(-0.1,0.1);
	y = -100.f;
	z = random(30, 35);
}
