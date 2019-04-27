#include "scene_proyecto.h"
#include "ifile.h"

#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <IL/il.h>

#define _USE_MATH_DEFINES
#define drand rand() / RAND_MAX
#include <math.h>


#define MAX_PARTICULAS 500 //1000

float x, y, z;

scene_proyecto::~scene_proyecto()
{
	// Borramos la memoria del ejecutable cuando
	// la escena deja de existir.
	glDeleteProgram(shader_program);
}

void scene_proyecto::init()
{
	scale = scaleM();
	Projection = projection();
	trans = translation(0, 0., 10.f);

	// createCube();
	initParticulas();
	std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0 }; //Front;
	
	// setColors();

	for (int i = 0; i < 6; i++)
	{

		textura.push_back(cgmath::vec2(1.0, 1.0));
		textura.push_back(cgmath::vec2(1.0, 0.0));
		textura.push_back(cgmath::vec2(0.0, 0.0));
		textura.push_back(cgmath::vec2(0.0, 1.0));
	}

	// Creacion y activacion del vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Creacion y configuracion del buffer del atributo de posicion
	glGenBuffers(1, &positionsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec3) * particulas.size(), particulas.data(), GL_STATIC_DRAW);
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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	// Creacion y configuracion del buffer del atributo de textura
	glGenBuffers(1, &texturasVBO);
	glBindBuffer(GL_ARRAY_BUFFER, texturasVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * textura.size(), textura.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); //unbind vao

	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	ilLoadImage("images/pig.png");

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

	//repetir cerdo

	/*cgmath::vec3 LightColor = cgmath::vec3(1.0f, 1.0f, 1.0f); //uniform

	ambiental = 10 % * LightColor;

	cgmath::vec3 LightPosition = cgmath::vec3(1.0f, 1.0f, 1.0f); //uniform

	difusse = normalize(Light) * normalize(PixelNormal);
	LightPosition = vec3();
	PixelPosition = VertexPosition * Model;


	R = reflect(-LightColor, PixelNormal);
	CamaraPosition = cos(R, V) *  LightColor;
	specular =
		cgmath::vec3 phong = ambient + diffuse + specular * TextureColor;
		*/
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

	shader_file.read("shaders/cube.frag");
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
	GLuint texture1_location = glGetUniformLocation(shader_program, "text1");
	glUniform1i(texture1_location, 0);
	GLuint texture2_location = glGetUniformLocation(shader_program, "text2");
	glUniform1i(texture2_location, 1);

	glUseProgram(0);

}

void scene_proyecto::awake()
{
	glClearColor(1.0f, 0.913f, 0.301f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void scene_proyecto::sleep()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_PROGRAM_POINT_SIZE);
}

void scene_proyecto::mainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	rotZ = rotateZ(moverCamara.z);
	rotY = rotateY(0);
	rotX = rotateX(moverCamara.x);
	matrizDeCamara = rotX * rotY * rotZ * scale * trans;

	Model = 1.0 * rotateX(0) * rotateY(0) * rotateZ(0) * scale * translation(0, 0, 0); //identidad x,y,z -> posicion matricula


	glUseProgram(shader_program);

	mxpMatrix = Projection * View * Model;
	GLuint mxpMatrix_location = glGetUniformLocation(shader_program, "mxpMatrix");
	glUniformMatrix4fv(mxpMatrix_location, 1, GL_FALSE, &mxpMatrix[0][0]);

	/*GLuint normal_location = glGetUniformLocation(shader_program, "mProyeccion");
	glUniformMatrix4fv(normal_location, 1, GL_FALSE, &Projection[0][0]);

	GLuint model_location = glGetUniformLocation(shader_program, "mVista");
	glUniformMatrix4fv(model_location, 1, GL_FALSE, &View[0][0]);

	GLuint model = glGetUniformLocation(shader_program, "mModelo");
	glUniformMatrix4fv(model, 1, GL_FALSE, &Model[0][0]);*/

	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0); // Se posicionan en el bucket 0
	glBindTexture(GL_TEXTURE_2D, textureId); // Activan la textura en ese bucket
	//cerdo

	// mxpMatrix = Projection * View * Model;
	View = cgmath::mat4::inverse(matrizDeCamara);

	// std::sort(positions.begin(), positions.end(), funCamara);
	for (int i = 0; i < MAX_PARTICULAS; i++)
	{
		y = positions[i].y - veclocidad[i].y;
		if (y > -bound) {
			veclocidad[i].y += aceleracion;
		} else {
			resetParticula(i);
		}
		
		GLuint pos_location = glGetUniformLocation(shader_program, "newPosition");
		glUniform3f(pos_location, positions[i].x, y, positions[i].z);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	glBindVertexArray(0);
	glUseProgram(0);

	// Dibuja su geometría
	glActiveTexture(GL_TEXTURE0); // Posicionarse en el bucket 0
	glBindTexture(GL_TEXTURE_2D, 0); // Desactivan la textura
}

void scene_proyecto::resize(int width, int height)
{
	mxpMatrix = Projection * View * Model;

	//Inicio, Fin (coordenadas)
	glViewport(0, 0, width, height);
	glUseProgram(shader_program);

	GLuint resolution_location = glGetUniformLocation(shader_program, "iResolution");
	glUniform2f(resolution_location, width, height);

	glUseProgram(0);

	aspect = width / height;
}

float scene_proyecto::radians(float grados) {
	return (grados * M_PI) / 180.;
}

cgmath::mat4 scene_proyecto::scaleM()
{
	return cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);
}

cgmath::mat4 scene_proyecto::translation(float x, float y, float z)
{
	return cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(x, y, z, 1.)
	);
}

//matriz unidad
cgmath::mat4 scene_proyecto::identidad()
{
	return cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);

}

cgmath::mat4 scene_proyecto::projection()
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

void scene_proyecto::setColors()
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

void scene_proyecto::initParticulas()
{
	//Front
	particulas.push_back(cgmath::vec3(-1., 1., 0.)); //v1 - 0
	particulas.push_back(cgmath::vec3(-1., -1., 0.)); //v2 - 1 
	particulas.push_back(cgmath::vec3(1., -1., 0.)); //v3 - 2
	particulas.push_back(cgmath::vec3(1., 1., 0.)); //v4 - 3

	for (int i = 0; i < MAX_PARTICULAS; i++)
	{
		/*	-30	30
			-30	30
		*/
		x = random(-bound, bound);
		y = random(bound, bound * 3);
		z = random(-bound/2, bound/2);
		positions.push_back(cgmath::vec4(x, y, z, 1.0f));
		veclocidad.push_back(cgmath::vec3(0, 0, 0));
	}

	moverCamara = cgmath::vec3(0, 0, 0);

}

void scene_proyecto::resetParticula(int i)
{
	GLfloat v;
	x = random(-bound, bound);
	y = random(bound, bound * 2);
	z = random(-bound/2, bound/2);

	positions[i] = cgmath::vec4(x, y, z, 1.0f);
	veclocidad[i] = cgmath::vec3(0, 0, 0);
}

float scene_proyecto::random(float fMin, float fMax) {
	return fMin + (rand() / (RAND_MAX / (fMax - fMin)));
}

void scene_proyecto::normalKeysDown(unsigned char key)
{
	switch (key) {
	case 'a':
		moverCamara.z -= 1;
		break;
	case 'd':
		moverCamara.z += 1;
		break;
	case 'w':
		moverCamara.x += 1;
		break;
	case 's':
		moverCamara.x -= 1;
		break;
	}
}

cgmath::mat4 scene_proyecto::rotateX(float iTime)
{
	return cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., cos(radians(iTime)), sin(radians(iTime)), 0.),
		cgmath::vec4(0., -sin(radians(iTime)), cos(radians(iTime)), 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);
}

cgmath::mat4 scene_proyecto::rotateY(float iTime)
{
	return cgmath::mat4(
		cgmath::vec4(cos(radians(iTime)), 0., -sin(radians(iTime)), 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(sin(radians(iTime)), 0., cos(radians(iTime)), 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);
}

cgmath::mat4 scene_proyecto::rotateZ(float iTime)
{
	return  cgmath::mat4(
		cgmath::vec4(cos(radians(iTime)), sin(radians(iTime)), 0., 0.),
		cgmath::vec4(-sin(radians(iTime)), cos(radians(iTime)), 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);
}
/*
bool funCamara(particula i, particula j)
{
	cgmath::vec3 d1 = i.camara - i.position;
	cgmath::vec3 d2 = j.camara - i.position;
	if (d1.magnitude() < d2.magnitude())
	{
		return true;
	}
	else
	{
		return false;
	}
}
*/