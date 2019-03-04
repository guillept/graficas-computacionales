#include "scene_vertex.h"
#include "ifile.h"
void scene_vertex::init()
{
	ifile shader_file;
	shader_file.read("shadersgrid.vert");
	std::string vertex_source = shader_file.get_contents();
	const GLchar* vertex_source_c = (const GLchar*) vertex_source.c_str(); //arreglo de chars

	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source_c, nullptr); //envias codigo a opengl
	glCompileShader(vertex_shader); //busca errores

	shader_file.read("shader/solid_color.frag");
	std::string fragment_source = shader_file.get_contents();
	const GLchar* fragment_source_c = (const GLchar*)fragment_source.c_str();
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source_c, nullptr);
	glCompileShader(vertex_shader);

	shader_program = glCreateProgram(); //manaeger
	glAttachShader(shader_program, vertex_shader); //administrar el identificador
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
}
scene_vertex::~scene_vertex()
{
}

void scene_vertex::awake()
{
}

void scene_vertex::sleep()
{
}

void scene_vertex::mainLoop()
{
}
