#include "scene_vertex.h"
#include "ifile.h"
#include "time.h"

#include <vector>
#include <iostream>

void scene_vertex::init()
{
	ifile shader_file;
	shader_file.read("shaders/grid.vert");
	std::string vertex_source = shader_file.get_contents();
	const GLchar* vertex_source_c = (const GLchar*) vertex_source.c_str(); //arreglo de chars

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source_c, nullptr); //envias codigo a opengl
	glCompileShader(vertex_shader); //busca errores


	/* GLint vertex_compiled;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_compiled);
	if (vertex_compiled != GL_TRUE)
	{
		GLint log_length;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);

		std::vector<GLchar> log;
		log.resize(log_length);
		glGetShaderInfoLog(vertex_shader, log_length, &log_length,
			&log[0]);
		std::cout << "Syntax errors in vertex shader: " << std::endl;
		for (int i = 0; i < log.size(); i++) std::cout << log[i];
	} */

	shader_file.read("shaders/solid_color.frag");
	std::string fragment_source = shader_file.get_contents();
	const GLchar* fragment_source_c = (const GLchar*)fragment_source.c_str();
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source_c, nullptr);
	glCompileShader(fragment_shader);

	shader_program = glCreateProgram(); //manaeger
	glAttachShader(shader_program, vertex_shader); //administrar el identificador
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader); //ya hay un ejecutable, borramos el shader
	glDeleteShader(fragment_shader);
}
scene_vertex::~scene_vertex()
{
	//liberar memoria
	glDeleteProgram(shader_program);
}

//cargar y guardar estado complejo de una escena, se llama cuando se va a dibujar esta escena
void scene_vertex::awake() 
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE); //cada unto puede tener un tama�o diferente
}

void scene_vertex::sleep()
{
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
	glDisable(GL_PROGRAM_POINT_SIZE);
}

void scene_vertex::mainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader_program);
	//posicion time
	GLuint time_location = glGetUniformLocation(shader_program, "time");
	glUniform1f(time_location, time::elapsed_time().count()); //envia el valor del tiempo transcurrido desde que empezo la escena
	glDrawArrays(GL_POINTS, 0, 100);//de 0 a 99
	glUseProgram(0);
}
