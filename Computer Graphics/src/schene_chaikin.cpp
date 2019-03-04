#include "schene_chaikin.h"

#include "vec2.h"
#include <vector>

//Se manda a llamar una vez cuando se inicia la aplicacion
void schene_chaikin::init() {
	std::vector<std::vector<cgmath::vec2>> positions;

	// std::vector<cgmath::vec2> positions;
	std::vector<cgmath::vec2> positions_oreja_derecha;
	std::vector<cgmath::vec2> positions_oreja_izquierda;

	positions_oreja_derecha.push_back(cgmath::vec2(-0.9f, -0.9f));
	positions_oreja_derecha.push_back(cgmath::vec2(-0.9f, 0.0f));
	positions.push_back(positions_oreja_derecha);

	positions_oreja_izquierda.push_back(cgmath::vec2(-0.9f, 0.0f));
	positions_oreja_izquierda.push_back(cgmath::vec2(0.0f, 0.0f));
	positions.push_back(positions_oreja_izquierda);

	/*
	positions.push_back(cgmath::vec2(-0.9f, -0.9f));
	positions.push_back(cgmath::vec2(-0.9f, 0.0f));
	positions.push_back(cgmath::vec2(0.0f, 0.0f));
	positions.push_back(cgmath::vec2(0.2f, -0.9f));
	positions.push_back(cgmath::vec2(0.9f, 0.9f)); 
	*/

	//Cara superior 
	/*
	positions.push_back(cgmath::vec2(-0.6f, -0.5f));
	positions.push_back(cgmath::vec2(-0.5f, -0.32f));
	positions.push_back(cgmath::vec2(-0.35f, -0.15f));
	positions.push_back(cgmath::vec2(-0.2f, -0.02f));
	positions.push_back(cgmath::vec2(0.12f, 0.03f));
	positions.push_back(cgmath::vec2(0.25f, 0.02f));
	positions.push_back(cgmath::vec2(0.35f, 0.01f));
	positions.push_back(cgmath::vec2(0.4f, 0.0f));
	positions.push_back(cgmath::vec2(0.6f, -0.08f));
	positions.push_back(cgmath::vec2(0.65f, -0.12f));
	positions.push_back(cgmath::vec2(0.7f, -0.15f));
	*/

	// Cara Inferior
	/*
	positions.push_back(cgmath::vec2(-0.56f, -0.55f));
	positions.push_back(cgmath::vec2(-0.35f, -0.53f));
	positions.push_back(cgmath::vec2(-0.2f, -0.5f));
	positions.push_back(cgmath::vec2(0.2f, -0.45f)); //cuello
	positions.push_back(cgmath::vec2(0.4f, -0.36f));
	positions.push_back(cgmath::vec2(0.5f, -0.33f));
	positions.push_back(cgmath::vec2(0.65f, -0.27f));
	positions.push_back(cgmath::vec2(0.7f, -0.25f));
	*/
	
	//Cuello
	/*
	positions.push_back(cgmath::vec2(0.0f, -0.45f));
	positions.push_back(cgmath::vec2(0.1f, -0.6f));
	positions.push_back(cgmath::vec2(0.15f, -0.58f));
	positions.push_back(cgmath::vec2(0.15f, -0.43f));
	*/
	//Pelo Izquierdo
	/*positions.push_back(cgmath::vec2(0.0f, 0.15f));
	positions.push_back(cgmath::vec2(-0.3f, 0.5f));
	positions.push_back(cgmath::vec2(-0.5f, 0.6f));
	positions.push_back(cgmath::vec2(-0.65f,0.65f)); //primer punta

	positions.push_back(cgmath::vec2(-0.65f, 0.65f)); 
	positions.push_back(cgmath::vec2(-0.45f, 0.4f));

	positions.push_back(cgmath::vec2(-0.45f, 0.4f)); //segunda punta
	positions.push_back(cgmath::vec2(-0.6f, 0.4f));
	positions.push_back(cgmath::vec2(-0.7f, 0.39f));

	positions.push_back(cgmath::vec2(-0.7f, 0.39f));
	positions.push_back(cgmath::vec2(-0.8f, 0.35f));
	positions.push_back(cgmath::vec2(-0.95f, 0.2f));

	
	positions.push_back(cgmath::vec2(-0.95f, 0.2f)); //tercera punta
	positions.push_back(cgmath::vec2(-0.7f, 0.18f));

	positions.push_back(cgmath::vec2(-0.7f, 0.18f));
	positions.push_back(cgmath::vec2(-0.8f, 0.1f));
	positions.push_back(cgmath::vec2(-0.9f, 0.0f));
	positions.push_back(cgmath::vec2(-0.95f, -0.1f));
	positions.push_back(cgmath::vec2(-0.95f, -0.18f));

	positions.push_back(cgmath::vec2(-0.95f, -0.18f)); //cuarta punta
	positions.push_back(cgmath::vec2(-0.78f, -0.1f));
	positions.push_back(cgmath::vec2(-0.78f, -0.1f));

	positions.push_back(cgmath::vec2(-0.87f, -0.3f));
	positions.push_back(cgmath::vec2(-0.87f, -0.4f));

	positions.push_back(cgmath::vec2(-0.87f, -0.4f)); //quinta punta
	positions.push_back(cgmath::vec2(-0.8f, -0.35f));
	positions.push_back(cgmath::vec2(-0.75f, -0.35f));
	positions.push_back(cgmath::vec2(-0.75f, -0.35f));

	positions.push_back(cgmath::vec2(-0.78f, -0.42f)); //sexta punta
	positions.push_back(cgmath::vec2(-0.80f, -0.45f));
	positions.push_back(cgmath::vec2(-0.80f, -0.5f));
	positions.push_back(cgmath::vec2(-0.79f, -0.52f)); 
	positions.push_back(cgmath::vec2(-0.77f, -0.55f));
	positions.push_back(cgmath::vec2(-0.77f, -0.55f));


	positions.push_back(cgmath::vec2(-0.7f, -0.5f));
	positions.push_back(cgmath::vec2(-0.65f, -0.47f));
	positions.push_back(cgmath::vec2(-0.6f, -0.5f));
	positions.push_back(cgmath::vec2(-0.6f, -0.5f)); */

	//Pelo Derecho
	/*
	positions.push_back(cgmath::vec2(0.05f, 0.1f)); //primer punta
	positions.push_back(cgmath::vec2(0.22f, 0.4f));
	positions.push_back(cgmath::vec2(0.5f, 0.65f));

	positions.push_back(cgmath::vec2(0.5f, 0.65f));
	positions.push_back(cgmath::vec2(0.47f, 0.56f));
	positions.push_back(cgmath::vec2(0.42f, 0.42f));

	positions.push_back(cgmath::vec2(0.42f, 0.42f)); //segunda punta
	positions.push_back(cgmath::vec2(0.6f, 0.5f));
	positions.push_back(cgmath::vec2(0.9f, 0.5f));

	positions.push_back(cgmath::vec2(0.9f, 0.5f));
	positions.push_back(cgmath::vec2(0.8f, 0.4f));
	positions.push_back(cgmath::vec2(0.7f, 0.25f));

	positions.push_back(cgmath::vec2(0.7f, 0.25f)); //tercer punta
	positions.push_back(cgmath::vec2(0.76f, 0.22f));
	positions.push_back(cgmath::vec2(0.95f, 0.1f)); 

	positions.push_back(cgmath::vec2(0.95f, 0.1f)); //cuarta punta
	positions.push_back(cgmath::vec2(0.9f, 0.08f));
	positions.push_back(cgmath::vec2(0.85f, 0.05f));
	positions.push_back(cgmath::vec2(0.8f, 0.0f));
	positions.push_back(cgmath::vec2(0.8f, 0.0f));

	
	positions.push_back(cgmath::vec2(0.8f, 0.0f));
	positions.push_back(cgmath::vec2(0.81f, -0.02f));
	positions.push_back(cgmath::vec2(0.95f, -0.1f));
	
	
	positions.push_back(cgmath::vec2(0.95f, -0.1f)); //quinta punta
	positions.push_back(cgmath::vec2(0.78f, -0.1f));
	positions.push_back(cgmath::vec2(0.7f, -0.15f));
	*/

	//Oreja Izquierda
	/* positions_oreja_izquierda.push_back(cgmath::vec2(-0.6f, -0.5f));
	positions_oreja_izquierda.push_back(cgmath::vec2(-0.64f, -0.5f));
	positions_oreja_izquierda.push_back(cgmath::vec2(-0.66f, -0.52f));
	positions_oreja_izquierda.push_back(cgmath::vec2(-0.66f, -0.56f));
	positions_oreja_izquierda.push_back(cgmath::vec2(-0.64f, -0.58f));
	positions_oreja_izquierda.push_back(cgmath::vec2(-0.62f, -0.59f));
	positions_oreja_izquierda.push_back(cgmath::vec2(-0.61f, -0.6f));
	positions_oreja_izquierda.push_back(cgmath::vec2(-0.6f, -0.59f));
	positions_oreja_izquierda.push_back(cgmath::vec2(-0.58f, -0.58f));
	positions_oreja_izquierda.push_back(cgmath::vec2(-0.56f, -0.56f));
	positions_oreja_izquierda.push_back(cgmath::vec2(-0.56f, -0.55f));
	positions.push_back(positions_oreja_izquierda);

	//Oreja Derecha
	positions_oreja_derecha.push_back(cgmath::vec2(0.7f, -0.15f));
	positions_oreja_derecha.push_back(cgmath::vec2(0.72f, -0.17f));
	positions_oreja_derecha.push_back(cgmath::vec2(0.74f, -0.16f));
	positions_oreja_derecha.push_back(cgmath::vec2(0.76f, -0.16f));
	positions_oreja_derecha.push_back(cgmath::vec2(0.78f, -0.17f));
	positions_oreja_derecha.push_back(cgmath::vec2(0.8f, -0.2f));
	positions_oreja_derecha.push_back(cgmath::vec2(0.8f, -0.23f));
	positions_oreja_derecha.push_back(cgmath::vec2(0.78f, -0.25f));
	positions_oreja_derecha.push_back(cgmath::vec2(0.77f, -0.26f));
	positions_oreja_derecha.push_back(cgmath::vec2(0.73f, -0.26f));
	positions_oreja_derecha.push_back(cgmath::vec2(0.71f, -0.24f));
	positions_oreja_derecha.push_back(cgmath::vec2(0.7f, -0.25f));
	positions.push_back(positions_oreja_derecha);*/

	// positions = schene_chaikin::calculate_chaikin(positions);

	size = positions.size();
	std::cout << positions.size() << std::endl; 

	//Crea un identificador y lo guarda en vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao); //se trabajara con el siguiente vao

		glGenBuffers(1, &positionsVBO); //Crea un identificador para el VBO, y guarda el id
		glBindBuffer(GL_ARRAY_BUFFER, positionsVBO); //quiero trabajar con el buffer positions VBO
	
		//crea la memoria del buffer, especifica los datos y la manda al GPU, G_DYNAMIC_DRAW es un hint pero openFl decide si hacerte caso o no

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ARRAY_BUFFER, ebo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * positions_oreja_derecha.size(), positions_oreja_derecha.data(), GL_DYNAMIC_DRAW);


		//orejaIzquierdaVBO - top
		// glGenBuffers(2, &ebo2);
		// glBindBuffer(GL_ARRAY_BUFFER, ebo2);
		// glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * positions_oreja_izquierda.size(), positions_oreja_izquierda.data(), GL_DYNAMIC_DRAW);
			

		glEnableVertexAttribArray(0);//prendo al atributo 0 
		/*configurar el atributo 0,
		numero de componentes,
		tipo de dato,
		normalizamos los dtos,
		desfazamineto entre los atribuutos en la lsita
		Apuntador a los datos*/
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0); 	// Unbind de positionsVBO			

	glBindVertexArray(0); // 0 = ubind del vao



	glGenVertexArrays(2, &vao2);
	glBindVertexArray(vao2);
	glGenBuffers(1, &positionsVBO); 
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	// orejaIzquierdaVBO - top
	glGenBuffers(2, &ebo2);
	glBindBuffer(GL_ARRAY_BUFFER, ebo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * positions_oreja_izquierda.size(), positions_oreja_izquierda.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);//prendo al atributo 0 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 	// Unbind de positionsVBO
	glBindVertexArray(0);

}

void schene_chaikin::awake() //en el momento del camnbio se manda a llamar awake
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glPointSize(20.0f);
}

void schene_chaikin::sleep()
{
	glPointSize(1.0f);
}

void schene_chaikin::mainLoop()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vao);
	glDrawArrays(GL_LINE_STRIP, 0, size);//llamada a dibujar, primitiva, a partir de donde y cuantos
	glBindVertexArray(0); //unbind


	glBindVertexArray(vao2);
	glDrawArrays(GL_LINE_STRIP, 0, size);//llamada a dibujar, primitiva, a partir de donde y cuantos
	glBindVertexArray(0); //unbind

}

std::vector<cgmath::vec2> schene_chaikin::calculate_chaikin(std::vector<cgmath::vec2> positions) {

	for (int j = 0; j < 2; j++)
	{
		std::vector<cgmath::vec2>  new_positions;

		for (int i = 0; i < positions.size() - 1; i++)
		{
			/* Qi = 3 / 4 * pi + 1 / 4 pi + 1;
		   Ri = 1 / 4Pi + 3 / 4 Pi + 1; */
			Qx = (3.0f / 4.0f * positions[i].x) + (1.0f / 4.0f * positions[i + 1].x);
			Qy = (3.0f / 4.0f * positions[i].y) + (1.0f / 4.0f * positions[i + 1].y);
			Rx = (1.0f / 4.0f * positions[i].x) + (3.0f / 4.0f * positions[i + 1].x);
			Ry = (1.0f / 4.0f * positions[i].y) + (3.0f / 4.0f * positions[i + 1].y);
			new_positions.push_back(cgmath::vec2(Qx, Qy));
			new_positions.push_back(cgmath::vec2(Rx, Ry));
		}

		positions = new_positions;

	}
	return positions;
}