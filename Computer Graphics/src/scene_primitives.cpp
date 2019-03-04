#include "scene_primitives.h"

#include "vec2.h"

#include <vector>

// Se manda a llamar una vez cuando inicia la aplicacion
void scene_primitives::init()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(0.0f, 0.0f));
	positions.push_back(cgmath::vec2(-1.0f, 0.0f));
	positions.push_back(cgmath::vec2(0.0f, -0.4f));
	positions.push_back(cgmath::vec2(1.0f, 0.0f));

	// Crear un identificador para un Vertex Array Object
	// Guarda el id en vao
	glGenVertexArrays(1, &vao);
	// Quiero empezar a trabajar con el siguiente vao
	glBindVertexArray(vao);

	// Crear un identificado para un Vertex Buffer Object
	// Guardar el id en positionsVBO
	glGenBuffers(1, &positionsVBO);
	// Quiero trabajar con el buffer positionsVBO
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	// Crea la memoria del buffer, especifica los datos y la manda al GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * positions.size(), positions.data(), GL_DYNAMIC_DRAW);
	// Prendo el atributo 0
	glEnableVertexAttribArray(0);
	// Voy a configurar el atributo 0
	// Numero de componentes
	// Tipo de dato de cada componente
	// Normalizamos los datos?
	// Desfazamiento entre los atributos en la lista
	// Apuntador a los datos si no los hemos mandado
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	// Cuando hacemos un bind con 0 -> unbind
	// Unbind de positionsVBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind del vao
	glBindVertexArray(0);

	primitiveType = GL_POINTS;
}

// Se manda a llamar cuando cambiamos a esta escena
void scene_primitives::awake()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPointSize(20.0f);
}

// Se manda a llamar cuando cambiamos a otra escena
void scene_primitives::sleep()
{
	glPointSize(1.0f);
}

// Se manda a llamar 1 vez por frame
void scene_primitives::mainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind del vao que tiene todos los atributos
	glBindVertexArray(vao);
	// Llamada a dibujar
	// Tipo de primitiva
	// Desde que vertice se empieza a dibujar
	// Cuantos vertices se dibujan
	glDrawArrays(primitiveType, 0, 4);
	// Unbind del vao y todos los atributos
	glBindVertexArray(0);
}

// Se manda a llamar cuando alguien presiona una tecla "normal".
// Una tecla normal es aquella que puede ser representada por un caracter,
// como letras o numeros.
void scene_primitives::normalKeysDown(unsigned char key)
{
	if (key == '1') primitiveType = GL_POINTS;
	if (key == '2') primitiveType = GL_LINES;
	if (key == '3') primitiveType = GL_LINE_STRIP;
	if (key == '4') primitiveType = GL_LINE_LOOP;
	if (key == '5') primitiveType = GL_TRIANGLES;
	if (key == '6') primitiveType = GL_TRIANGLE_STRIP;
	if (key == '7') primitiveType = GL_TRIANGLE_FAN;
}