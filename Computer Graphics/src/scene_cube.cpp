#include "scene_cube.h"

#include "ifile.h"
#include "time.h"

#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

scene_cube::~scene_cube()
{
	// Borramos la memoria del ejecutable cuando
	// la escena deja de existir.
	glDeleteProgram(shader_program);
}

void scene_cube::init()
{
	std::vector<cgmath::vec3> positions;
	std::vector<cgmath::vec3> colors;

	//Matriz de modelo translation*rotation*scale
	float iTime = time::elapsed_time().count();

	rotZ = cgmath::mat4(
		cgmath::vec4(cos(radians(30.)*iTime), sin(radians(30.)*iTime), 0., 0.),
		cgmath::vec4(-sin(radians(30.)*iTime), cos(radians(30.)*iTime), 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);

	rotY = cgmath::mat4(
		cgmath::vec4(cos(radians(60.)*iTime), 0., -sin(radians(60.)*iTime), 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(sin(radians(60.)*iTime), 0., cos(radians(60.)*iTime), 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);

	rotX = cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., cos(radians(30.)*iTime), sin(radians(30.)*iTime), 0.),
		cgmath::vec4(0., -sin(radians(30.)*iTime), cos(radians(30.)*iTime), 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);

	scale = cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);

	trans = cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);


	cgmath::mat4 matrizDeCamara(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(0., 0., 10., 1.)
	);

	float near = 1.0f;
	float far = 1000.f;
	float fov = radians(60.);

	Model = rotX * rotY * rotZ * scale * trans;
	View = cgmath::mat4::inverse(matrizDeCamara);
	Projection = cgmath::mat4(
		cgmath::vec4(1. / (aspect*tan(fov / 2.)), 0., 0., 0.),
		cgmath::vec4(0., 1. / (tan(fov / 2.)), 0., 0.),
		cgmath::vec4(0., 0., -((far + near) / (far - near)), -1.),
		cgmath::vec4(0., 0., -((2 * far*near) / (far - near)), 1.)
	);

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

	std::vector<unsigned int> indices =
	{
		0, 1, 2, 2, 3, 0, //Front
		4, 5, 6, 6, 7, 4, //Right
		11, 10, 9, 9, 8, 11, //Back
		14, 13, 12, 12, 15, 14, //Left
		16, 17, 18, 18, 19, 16, //Top
		20, 21, 22, 22, 23, 20,//Bottom

	};

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
	glGenBuffers(2, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec3) * colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); //unbind vao

	ifile shader_file;
	shader_file.read("shaders/cube.vert");
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

	glLinkProgram(shader_program);

	// Borramos los shaders, porque ya tenemos el ejecutable
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glUseProgram(shader_program);
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

void scene_cube::mainLoop()
{
	float iTime = time::elapsed_time().count();

	rotZ = cgmath::mat4(
		cgmath::vec4(cos(radians(30.)*iTime), sin(radians(30.)*iTime), 0., 0.),
		cgmath::vec4(-sin(radians(30.)*iTime), cos(radians(30.)*iTime), 0., 0.),
		cgmath::vec4(0., 0., 1., 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);

	rotY = cgmath::mat4(
		cgmath::vec4(cos(radians(60.)*iTime), 0., -sin(radians(60.)*iTime), 0.),
		cgmath::vec4(0., 1., 0., 0.),
		cgmath::vec4(sin(radians(60.)*iTime), 0., cos(radians(60.)*iTime), 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);

	rotX = cgmath::mat4(
		cgmath::vec4(1., 0., 0., 0.),
		cgmath::vec4(0., cos(radians(30.)*iTime), sin(radians(30.)*iTime), 0.),
		cgmath::vec4(0., -sin(radians(30.)*iTime), cos(radians(30.)*iTime), 0.),
		cgmath::vec4(0., 0., 0., 1.)
	);

	Model = rotX * rotY * rotZ * scale * trans;
	mxpMatrix = Projection * View * Model;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_program);

	GLuint mxpMatrix_location = glGetUniformLocation(shader_program, "mxpMatrix");
	glUniformMatrix4fv(mxpMatrix_location, 1, GL_FALSE, &mxpMatrix[0][0]);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr); //gl_trinagle_strip
	glBindVertexArray(0);
	glUseProgram(0);
}

void scene_cube::resize(int width, int height)
{
	mxpMatrix = Projection * View * Model;

	//Inicio, Fin (coordenadas)
	glViewport(0, 0, width, height);
	glUseProgram(shader_program);
	GLuint resolution_location = glGetUniformLocation(shader_program, "iResolution");
	glUniform2f(resolution_location, width, height);

	GLuint mxpMatrix_location = glGetUniformLocation(shader_program, "mxpMatrix");
	glUniformMatrix4fv(mxpMatrix_location, 1, GL_FALSE, &mxpMatrix[0][0]);
	glUseProgram(0);

	aspect = width / height;
}

float scene_cube::radians(float grados) {
	return (grados * M_PI) / 180.;
}