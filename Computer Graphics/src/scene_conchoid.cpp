#include "scene_conchoid.h"

#include "vec2.h"
#include <vector>


//Se manda a llamar una vez cuando se inicia la aplicacion
void scene_conchoid::init() {
	std::vector<cgmath::vec2>  positions;
	positions.push_back(cgmath::vec2(0.0f, 0.0f));
	positions.push_back(cgmath::vec2(-1.0f, 0.0f));
	positions.push_back(cgmath::vec2(0.0f, -0.4f));
	positions.push_back(cgmath::vec2(1.0f, 0.0f));

	//Crea un identificador y lo guarda en vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao); //se traabajara con el siguiente vao

	glGenBuffers(1, &positionsVBO); //Crea un identificador para el VBO, y guarda el id
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO); //quiero trabajar con el buffer positions VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * positions.size(), positions.data(), GL_DYNAMIC_DRAW); //crea la memoria del buffer, especifica los datos y la manda al GPU, G_DYNAMIC_DRAW es un hint pero openFl decide si hacerte caso o no
	glEnableVertexAttribArray(0);//prendo al atributo 0 

	/*configurar el atributo 0,
	numero de componentes,
	tipo de dato,
	normalizamos los dtos,
	desfazamineto entre los atribuutos en la lsita
	Apuntador a los datos*/
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // 0 = unbind
	glBindVertexArray(0); // 0 = ubind del vao

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

	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, 4);//llamada a dibujar, primitiva, a partir de donde y cuantos
	glBindVertexArray(0); //unbind

}
