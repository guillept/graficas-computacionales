#include "schene_chaikin.h"

#include "vec2.h"
#include <vector>


//Se manda a llamar una vez cuando se inicia la aplicacion
void schene_chaikin::init() {

	std::vector<std::vector<cgmath::vec2>> positions;

	/* positions.push_back(cgmath::vec2(0.9f, -0.9f));
	positions.push_back(cgmath::vec2(0.9f, 0.9f));
	std::cout << positions.size() << std::endl;
	positions.push_back(positions);

	positions.push_back(cgmath::vec2(-0.9f, -0.9f));
	positions.push_back(cgmath::vec2(-0.9f, 0.0f));
	positions.push_back(cgmath::vec2(0.0f, 0.0f));
	positions.push_back(cgmath::vec2(0.2f, -0.9f));
	positions.push_back(cgmath::vec2(0.7f, 0.9f));
	positions = schene_chaikin::calculate_chaikin(positions);
	std::cout << positions.size() << std::endl;
	positions.push_back(positions);
	*/

	/*
	positions.push_back(cgmath::vec2(-0.9f, -0.9f));
	positions.push_back(cgmath::vec2(-0.9f, 0.0f));
	positions.push_back(cgmath::vec2(0.0f, 0.0f));
	positions.push_back(cgmath::vec2(0.2f, -0.9f));
	positions.push_back(cgmath::vec2(0.9f, 0.9f)); 
	*/
	

	//Pelo Izquierdo
	positions.push_back(schene_chaikin::calculate_chaikin(createCabelloIzquierdo()));
	size_0 = positions[0].size();
	std::cout << size_0 << std::endl;
	//Pelo Derecho
	positions.push_back(schene_chaikin::calculate_chaikin(createCabelloDerecho()));
	size_1 = positions[1].size();
	std::cout << size_1 << std::endl;
	//Oreja Izquierda
	positions.push_back(schene_chaikin::calculate_chaikin(createOrejaIzquierdo()));
	size_2 = positions[2].size();
	std::cout << size_2 << std::endl;
	//Oreja Derecha
	positions.push_back(schene_chaikin::calculate_chaikin(createOrejaDerecho()));
	size_3 = positions[3].size();
	//Cara superior 
	positions.push_back(schene_chaikin::calculate_chaikin(createCabezaSuperior()));
	size_4 = positions[4].size();
	// Cara Inferior
	positions.push_back(schene_chaikin::calculate_chaikin(createCabezaInferior()));
	size_5 = positions[5].size();
	positions.push_back(schene_chaikin::calculate_chaikin(createCabezaInferior_B()));
	size_6 = positions[6].size();

	//Cuello
	positions.push_back(createCuello());
	size_7 = positions[7].size();
	

	createVao(1, positions[0]);
	createVao(2, positions[1]);
	createVao(3, positions[2]);
	createVao(4, positions[3]);
	createVao(5, positions[4]);
	createVao(6, positions[5]);
	createVao(7, positions[6]);
	createVao(8, positions[7]);


	/* glGenVertexArrays(2, &vao2);
	glBindVertexArray(vao2);
	glGenBuffers(1, &positionsVBO); 
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	// orejaIzquierdaVBO - top
	glGenBuffers(2, &ebo2);
	glBindBuffer(GL_ARRAY_BUFFER, ebo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * positions.size(), positions.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);//prendo al atributo 0 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 	// Unbind de positionsVBO
	glBindVertexArray(0);

	/* for (int i = 0; i < 4; i++)
	{ 
		std::cout << vaos[i] << std::endl;
		glGenVertexArrays(i+1, &(vaos[i]));
		glBindVertexArray(vaos[i]);
		glGenBuffers(1, &positionsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
		glGenBuffers(2, &ebo);
		glBindBuffer(GL_ARRAY_BUFFER, ebo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * positions[i].size(), positions[i].data(), GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);//prendo al atributo 0 
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0); 	// Unbind de positionsVBO
		glBindVertexArray(0);

	} */

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

	glBindVertexArray(vao0);
	glDrawArrays(GL_LINE_STRIP, 0, 146);//llamada a dibujar, primitiva, a partir de donde y cuantos
	glBindVertexArray(0); //unbind

	glBindVertexArray(vao1);
	glDrawArrays(GL_LINE_STRIP, 0, 102);//llamada a dibujar, primitiva, a partir de donde y cuantos
	glBindVertexArray(0); //unbind

	glBindVertexArray(vao2);
	glDrawArrays(GL_LINE_STRIP, 0, 42);//llamada a dibujar, primitiva, a partir de donde y cuantos
	glBindVertexArray(0); //unbind

	glBindVertexArray(vao3);
	glDrawArrays(GL_LINE_STRIP, 0, size_3);//llamada a dibujar, primitiva, a partir de donde y cuantos
	glBindVertexArray(0); //unbind

	glBindVertexArray(vao4);
	glDrawArrays(GL_LINE_STRIP, 0, size_4);//llamada a dibujar, primitiva, a partir de donde y cuantos
	glBindVertexArray(0); //unbind

	glBindVertexArray(vao5);
	glDrawArrays(GL_LINE_STRIP, 0, size_5);//llamada a dibujar, primitiva, a partir de donde y cuantos
	glBindVertexArray(0); //unbind

	glBindVertexArray(vao6);
	glDrawArrays(GL_LINE_STRIP, 0, size_6);//llamada a dibujar, primitiva, a partir de donde y cuantos
	glBindVertexArray(0); //unbind

	glBindVertexArray(vao7);
	glDrawArrays(GL_LINE_STRIP, 0, size_7);//llamada a dibujar, primitiva, a partir de donde y cuantos
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

void schene_chaikin::createVao(int i, std::vector<cgmath::vec2> position) {
	if (i == 1) {
		//Crea un identificador y lo guarda en vao
		glGenVertexArrays(i, &vao0);
		glBindVertexArray(vao0); //se trabajara con el siguiente vao
	}
	else if (i == 2) {
		//Crea un identificador y lo guarda en vao
		glGenVertexArrays(i, &vao1);
		glBindVertexArray(vao1); //se trabajara con el siguiente vao
	}
	else if (i == 3) {
		//Crea un identificador y lo guarda en vao
		glGenVertexArrays(i, &vao2);
		glBindVertexArray(vao2); //se trabajara con el siguiente vao
	}
	else if (i == 4) {
		//Crea un identificador y lo guarda en vao
		glGenVertexArrays(i, &vao3);
		glBindVertexArray(vao3); //se trabajara con el siguiente vao
	}
	else if (i == 5) {
		//Crea un identificador y lo guarda en vao
		glGenVertexArrays(i, &vao4);
		glBindVertexArray(vao4); //se trabajara con el siguiente vao
	}
	else if (i == 6) {
		//Crea un identificador y lo guarda en vao
		glGenVertexArrays(i, &vao5);
		glBindVertexArray(vao5); //se trabajara con el siguiente vao
	}
	else if (i == 7) {
		//Crea un identificador y lo guarda en vao
		glGenVertexArrays(i, &vao6);
		glBindVertexArray(vao6); //se trabajara con el siguiente vao
	}
	else if (i == 8) {
		//Crea un identificador y lo guarda en vao
		glGenVertexArrays(i, &vao7);
		glBindVertexArray(vao7); //se trabajara con el siguiente vao
	}


	glGenBuffers(1, &positionsVBO); //Crea un identificador para el VBO, y guarda el id
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO); //quiero trabajar con el buffer positions VBO

	glGenBuffers(i, &ebo);
	glBindBuffer(GL_ARRAY_BUFFER, ebo);
	//crea la memoria del buffer, especifica los datos y la manda al GPU, G_DYNAMIC_DRAW es un hint pero openFl decide si hacerte caso o no
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * position.size(), position.data(), GL_DYNAMIC_DRAW);
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

}

std::vector<cgmath::vec2> schene_chaikin::createCabelloIzquierdo() {

	std::vector<cgmath::vec2> positions;

	positions.push_back(cgmath::vec2(0.0f, 0.15f));
	positions.push_back(cgmath::vec2(-0.3f, 0.5f));
	positions.push_back(cgmath::vec2(-0.5f, 0.6f));
	positions.push_back(cgmath::vec2(-0.65f, 0.65f)); //primer punta

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
	positions.push_back(cgmath::vec2(-0.6f, -0.5f));

	return positions;

}

std::vector<cgmath::vec2> schene_chaikin::createCabelloDerecho(){

	std::vector<cgmath::vec2> positions;

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
	positions.push_back(cgmath::vec2(0.7f, -0.15f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createOrejaIzquierdo() {

	std::vector<cgmath::vec2> positions;

	positions.push_back(cgmath::vec2(-0.6f, -0.5f));
	positions.push_back(cgmath::vec2(-0.6f, -0.5f));
	positions.push_back(cgmath::vec2(-0.65f, -0.5f));
	positions.push_back(cgmath::vec2(-0.66f, -0.52f));
	positions.push_back(cgmath::vec2(-0.66f, -0.56f));
	positions.push_back(cgmath::vec2(-0.64f, -0.58f));
	positions.push_back(cgmath::vec2(-0.62f, -0.59f));
	positions.push_back(cgmath::vec2(-0.61f, -0.6f));
	positions.push_back(cgmath::vec2(-0.6f, -0.59f));
	positions.push_back(cgmath::vec2(-0.58f, -0.58f));
	positions.push_back(cgmath::vec2(-0.56, -0.55f));
	positions.push_back(cgmath::vec2(-0.56, -0.55f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createOrejaDerecho() {

	std::vector<cgmath::vec2> positions;

	positions.push_back(cgmath::vec2(0.7f, -0.15f));
	positions.push_back(cgmath::vec2(0.7f, -0.15f));
	positions.push_back(cgmath::vec2(0.72f, -0.17f));
	positions.push_back(cgmath::vec2(0.74f, -0.16f));
	positions.push_back(cgmath::vec2(0.76f, -0.16f));
	positions.push_back(cgmath::vec2(0.78f, -0.17f));
	positions.push_back(cgmath::vec2(0.8f, -0.2f));
	positions.push_back(cgmath::vec2(0.8f, -0.23f));
	positions.push_back(cgmath::vec2(0.78f, -0.25f));
	positions.push_back(cgmath::vec2(0.77f, -0.26f));
	positions.push_back(cgmath::vec2(0.73f, -0.26f));
	positions.push_back(cgmath::vec2(0.71f, -0.24f));
	positions.push_back(cgmath::vec2(0.7f, -0.25f));
	positions.push_back(cgmath::vec2(0.7f, -0.25f));

	return positions;

}

std::vector<cgmath::vec2> schene_chaikin::createCabezaInferior()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(-0.56, -0.55f));
	positions.push_back(cgmath::vec2(-0.56f, -0.55f));
	positions.push_back(cgmath::vec2(-0.35f, -0.53f));
	positions.push_back(cgmath::vec2(-0.2f, -0.5f)); 
	positions.push_back(cgmath::vec2(0.17f, -0.45f));//cuello

	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createCabezaInferior_B()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(0.14f, -0.46f));
	positions.push_back(cgmath::vec2(0.14f, -0.46f));
	positions.push_back(cgmath::vec2(0.2f, -0.44f));
	positions.push_back(cgmath::vec2(0.4f, -0.36f));
	positions.push_back(cgmath::vec2(0.5f, -0.33f));
	positions.push_back(cgmath::vec2(0.65f, -0.27f));
	positions.push_back(cgmath::vec2(0.7f, -0.25f));
	positions.push_back(cgmath::vec2(0.7f, -0.25f));

	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createCabezaSuperior()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(-0.6f, -0.5f));
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
	positions.push_back(cgmath::vec2(0.7f, -0.15f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createCuello()
{
	std::vector<cgmath::vec2> positions;

	positions.push_back(cgmath::vec2(0.01f, -0.47f));
	positions.push_back(cgmath::vec2(0.09f, -0.62f));
	positions.push_back(cgmath::vec2(0.14f, -0.58f));
	positions.push_back(cgmath::vec2(0.14f, -0.46f));

	return positions;
}
