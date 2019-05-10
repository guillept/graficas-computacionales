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
	glDeleteProgram(shader_program);
}

void scene_fuego::init()
{
	//Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Projection = projection();
	trans = translation(0, 0., 80.f);

	initParticulas();
	setTexturas();
	std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 }; //Front;

	// setColors();

	// Creacion y activacion del vao
	glGenVertexArrays(1, &vao);
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

	// Creacion y configuracion del buffer del atributo de color
	/*glGenBuffers(1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_GLfloat, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	// Creacion y configuracion del buffer del atributo de textura
	glGenBuffers(1, &texturasVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texturasVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * textura.size(), textura.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
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

	ifile shader_file;
	shader_file.read("shaders/particulas.vert");
	std::string vertex_source = shader_file.get_contents();
	const GLchar* vertex_source_c = (const GLchar*)vertex_source.c_str();
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source_c, nullptr);
	glCompileShader(vertex_shader);

	// Revision de errores de compilacion del vertex shader
	GLint vertex_compiled;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_compiled);
	if (vertex_compiled != GL_TRUE)
	{
		GLint log_length;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);

		std::vector<GLchar> log;
		log.resize(log_length);
		glGetShaderInfoLog(vertex_shader, log_length, &log_length, &log[0]);
		std::cout << "Syntax errors in vertex shader: " << std::endl;
		for (auto& c : log) std::cout << c;
		std::cout << std::endl;
	}

	shader_file.read("shaders/particulas.frag");
	std::string fragment_source = shader_file.get_contents();
	const GLchar* fragment_source_c = (const GLchar*)fragment_source.c_str();
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source_c, nullptr);
	glCompileShader(fragment_shader);

	// Revision de errores de compilacion del fragment shader
	GLint fragment_compiled;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_compiled);
	if (fragment_compiled != GL_TRUE)
	{
		GLint log_length;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);

		std::vector<GLchar> log;
		log.resize(log_length);
		glGetShaderInfoLog(fragment_shader, log_length, &log_length, &log[0]);
		std::cout << "Syntax errors in fragment shader: " << std::endl;
		for (auto& c : log) std::cout << c;
		std::cout << std::endl;
	}

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);

	// Asignar Buffer a variables de IN en VertexShader
	glBindAttribLocation(shader_program, 0, "VertexPosition");
	glBindAttribLocation(shader_program, 1, "InterpolatedColor");
	glBindAttribLocation(shader_program, 2, "TexturePosition");
	glLinkProgram(shader_program);

	// Borramos los shaders, porque ya tenemos el ejecutable
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	glUseProgram(shader_program);

	// cgmath::vec3 LightColor = cgmath::vec3(1.0f, 1.0f, 1.0f); //uniform
	GLuint lightcolor_location = glGetUniformLocation(shader_program, "LightColor");
	glUniform3f(lightcolor_location, 1.0f, 1.0f, 1.0f);

	//cgmath::vec3 LightPosition = cgmath::vec3(1.0f, 1.0f, 1.0f); //uniform
	GLuint lightpos_location = glGetUniformLocation(shader_program, "LightPosition");
	glUniform3f(lightpos_location, 0.0f, 0.0f, -bound - 10);

	GLuint campos_location = glGetUniformLocation(shader_program, "CameraPosition");
	glUniform3f(campos_location, 0.0f, 0.0f, 80.f);

	GLuint texture1_location = glGetUniformLocation(shader_program, "texture");
	glUniform1i(texture1_location, 0);

	glUseProgram(0);

}

void scene_fuego::awake()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void scene_fuego::sleep()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDisable(GL_PROGRAM_POINT_SIZE);
}

void scene_fuego::mainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// matrizDeCamara = rotX * rotY * rotZ * scale * trans; 
	// rotY y scale se eliminan = identidad
	matrizDeCamara = rotateX(moverCamara.x) *  rotateZ(moverCamara.z) * trans;
	View = cgmath::mat4::inverse(matrizDeCamara);

	glUseProgram(shader_program);

	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0); // Se posicionan en el bucket 0
	glBindTexture(GL_TEXTURE_2D, textureId); // Activan la textura en ese bucket

	std::sort(&particulas[0], &particulas[MAX_PARTICULAS - 1]);
	willPartiTheParticleLive = 0;

	for (int i = 0; i < MAX_PARTICULAS; i++)
	{
		index = particulas[i].position;
		lifes[index] -= 1.0;
		//is particle alive?
		if (lifes[index] > 0) {

			particulas[i].distance = calculateDistance(index);
		
			positions[index].x += veclocidad[index].x;
			positions[index].y += veclocidad[index].y;
			positions[index].z += veclocidad[index].z;

			veclocidad[index].x = aceleracion[index].x * time::delta_time().count(); //Vf = a*t + Vo
			veclocidad[index].y = aceleracion[index].y * time::delta_time().count(); //Vf = a*t + Vo
			veclocidad[index].z = aceleracion[index].z * time::delta_time().count(); //Vf = a*t + Vo

			// Model = rotateX(0) * rotateY(0) * rotateZ(0) * scale * translation(positions[index].x, positions[index].y, positions[index].z);
			// rotX, rotY, rotZ y scale se eliminan = identidad
			Model = translation(positions[index].x, positions[index].y, positions[index].z); //identidad x,y,z -> posicion matriculaS

			billboard();
			// mxpMatrix = Projection * View * Model;
			mxpMatrix = Projection * ViewModel;

			GLuint model_location = glGetUniformLocation(shader_program, "modelMatrix");
			glUniformMatrix4fv(model_location, 1, GL_FALSE, &Model[0][0]);

			GLuint mxpMatrix_location = glGetUniformLocation(shader_program, "mxpMatrix");
			glUniformMatrix4fv(mxpMatrix_location, 1, GL_FALSE, &mxpMatrix[0][0]);

			/*GLuint pos_location = glGetUniformLocation(shader_program, "newPosition");
			glUniform3f(pos_location, positions[index].x, positions[index].y, positions[index].z);*/
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
		//particle is dead
		else {
			willPartiTheParticleLive = random(1, 500);
			if (willPartiTheParticleLive >= 499) {
				resetParticula(index);
			}
		}
	}

	glBindVertexArray(0);
	glUseProgram(0);

	// Dibuja su geometría
	glActiveTexture(GL_TEXTURE0); // Posicionarse en el bucket 0
	glBindTexture(GL_TEXTURE_2D, 0); // Desactivan la textura
}

void scene_fuego::resize(int width, int height)
{
	//Inicio, Fin (coordenadas)
	glViewport(0, 0, width, height);
	aspect = width / height;
}

GLfloat scene_fuego::radians(GLfloat grados) {
	return (grados * M_PI) / 180.;
}

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
	float near = 1.0f;
	float far = 1000.f;
	float fov = radians(60.);

	return cgmath::mat4(
		cgmath::vec4(1. / (aspect*tan(fov / 2.)), 0., 0., 0.),
		cgmath::vec4(0., 1. / (tan(fov / 2.)), 0., 0.),
		cgmath::vec4(0., 0., -((far + near) / (far - near)), -1.),
		cgmath::vec4(0., 0., -((2 * far*near) / (far - near)), 1.)
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

void scene_fuego::setColors()
{
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
}

void scene_fuego::resetParticula(int i)
{
	setXYZ();
	positions[i] = cgmath::vec4(x, y, z, 1.0f);
	veclocidad[i] = cgmath::vec3(0, 0, 0);
	lifes[i] = lifeTime;
	aceleracion[index].x = random(-maxAceleracion, maxAceleracion);
	aceleracion[index].y = random(gravedad, gravedad*3);
	aceleracion[index].z = random(-maxAceleracion, maxAceleracion);
}

GLfloat scene_fuego::random(GLfloat fMin, GLfloat fMax) {
	return fMin + (rand() / (RAND_MAX / (fMax - fMin)));
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
	}
}

cgmath::vec3 scene_fuego::calculateDistance(int i)
{
	// Column 3
	cgmath::vec3 camara = cgmath::vec3(matrizDeCamara[3][0], matrizDeCamara[3][1], matrizDeCamara[3][2]);
	cgmath::vec3 position_particula = cgmath::vec3(positions[i].x, positions[i].y, positions[i].z);
	return camara - position_particula;
}

void scene_fuego::billboard()
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

void scene_fuego::setXYZ()
{
	x = random(-5, 5);
	y = (-60, -50);
	z = random(-bound, bound);
}
