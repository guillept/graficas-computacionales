#include "scene_conchoid.h"

#include "vec2.h"
#include <vector>
#include <math.h>


//Se manda a llamar una vez cuando se inicia la aplicacion
void scene_conchoid::init() {

	positions.push_back(calcularConchoid(0));
	positions.push_back(calcularConchoid(1));

	for (int i = 1; i <= positions.size(); i++)
	{
		createVao(i, positions[i - 1]);
	}
}

void scene_conchoid::awake() //en el momento del camnbio se manda a llamar awake
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPointSize(20.0f);
}

void scene_conchoid::sleep()
{
	glPointSize(1.0f);
}

void scene_conchoid::mainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < positions.size(); i++)
	{
		glBindVertexArray(vaos[i]);
		glDrawArrays(GL_LINE_STRIP, 0, positions[i].size());//llamada a dibujar, primitiva, a partir de donde y cuantos
		glBindVertexArray(0); //unbind 
	}

}

std::vector<cgmath::vec2> scene_conchoid::calcularConchoid(int inverso)
{
	std::vector<cgmath::vec2> conchoid;

	//(x-a)^2(x^2+y^2)=b^2x^2 a/b = 1/2
	double y, a = 2.5, b = 5;

	for (double x = -2.5; x <= 7.5; x+=0.1)
	{
		y = (pow(b, 2) * pow(x, 2)) / (pow(x, 2) - (2 * a*x) + pow(a, 2));
		y = (inverso == 0) ? sqrt(y - pow(x, 2)) : -sqrt(y - pow(x, 2));
		conchoid.push_back(cgmath::vec2(x, y) / 20); // escalar
	}
	return conchoid;
}

void scene_conchoid::createVao(int i, std::vector<cgmath::vec2> position)
{
	glGenVertexArrays(i, &vaos[i - 1]);
	glBindVertexArray(vaos[i - 1]); //se trabajara con el siguiente vao
	glGenBuffers(1, &positionsVBO); //Crea un identificador para el VBO, y guarda el id
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO); //quiero trabajar con el buffer positions VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * position.size(), position.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);//prendo al atributo 0 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 	// Unbind de positionsVBO			
	glBindVertexArray(0); // 0 = ubind del vao

}
