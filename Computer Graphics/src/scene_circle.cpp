#include "scene_circle.h"

#include "ifile.h"
#include "time.h"
#include "vec2.h"
#include "vec3.h"

#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

scene_circle::~scene_circle()
{
	// Borramos la memoria del ejecutable cuando
	// la escena deja de existir.
	glDeleteProgram(shader_program);
}

void scene_circle::init()
{
	std::vector<cgmath::vec2> positions;
	std::vector<cgmath::vec3> colors;

	float x, y, z, angle, r,g, b;

	std::vector<unsigned int> indices;

	positions.push_back(cgmath::vec2(0., 0.)); //definir centro
	for (int i = 0; i <= TOTAL_SIDES + 1; i++)
	{
		angle =  (i* M_PI) / 180 ; //calcular radianes
		x = radius * cos(angle);
		y = radius * sin(angle);

		if (i == 0) {
			r = 1.0f;
			g = 1.0f;
			b = 1.0f;
		}
		else {
			r = x;
			g = y - x;
			b = -y - x;
		}

		positions.push_back(cgmath::vec2(x, y));
		indices.push_back(i);
		colors.push_back(cgmath::vec3(r, g, b));
	}

	// Creacion y activacion del vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Creacion y configuracion del buffer del atributo de posicion
	glGenBuffers(1, &positionsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * positions.size(), positions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
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

	glBindVertexArray(0); //unbind vao

	ifile shader_file;
	shader_file.read("shaders/circle.vert");
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

	shader_file.read("shaders/circle.frag");
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
	GLuint resolution_location = glGetUniformLocation(shader_program, "iResolution");

	glUniform2f(resolution_location, 400.0f, 400.0f);
	glUseProgram(0);

}

void scene_circle::awake()
{
	glClearColor(1.0f, 0.913f, 0.301f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void scene_circle::sleep()
{
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
	glDisable(GL_PROGRAM_POINT_SIZE);
}

void scene_circle::mainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader_program);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLE_FAN, TOTAL_VERTICES, GL_UNSIGNED_INT, nullptr); //gl_trinagle_strip
	glBindVertexArray(0);
	glUseProgram(0);
}

void scene_circle::resize(int width, int height)
{
	//Inicio, Fin (coordenadas)
	glViewport(0, 0, width, height);
	glUseProgram(shader_program);
	GLuint resolution_location = glGetUniformLocation(shader_program, "iResolution");
	glUniform2f(resolution_location, width, height);
	glUseProgram(0);
}

