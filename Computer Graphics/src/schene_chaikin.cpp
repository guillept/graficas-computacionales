#include "schene_chaikin.h"

#include "vec2.h"
#include <vector>

void schene_chaikin::init() {

	linesFigure();
	lineStripFigure();

 	for (int i = 1; i <= positions.size(); i++)
	{
		createVao(i, positions[i-1]);
	}
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

	if (displayLines) {
		for (int i = 0; i < positions.size() / 2; i++) //dibujar segmentos sin algoritmo chaikin
			draw(i, GL_LINES);
	}
	if (displayLineStrip) 
	{
		for (int i = positions.size() / 2 ; i < positions.size(); i++) //dibujar segmentos con algoritmo chaikin (dibujo final)
			draw(i, GL_LINE_STRIP);
	} 
}

void schene_chaikin::draw(int i, GLenum primitiveType) {
	glBindVertexArray(vaos[i]);
	if (positions[i].size() == 1) {
		glPointSize(7.0f);
		glDrawArrays(GL_POINTS, 0, positions[i].size());
	}
	else {
		glDrawArrays(primitiveType, 0, positions[i].size());//llamada a dibujar, primitiva, a partir de donde y cuantos
	}
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

	glGenVertexArrays(i, &vaos[i-1]);
	glBindVertexArray(vaos[i-1]);
	glGenBuffers(1, &positionsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cgmath::vec2) * position.size(), position.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);		
	glBindVertexArray(0); 
}

std::vector<cgmath::vec2> schene_chaikin::createCabelloIzquierdo() {

	std::vector<cgmath::vec2> positions;

	positions.push_back(cgmath::vec2(0.03f, 0.28f));
	positions.push_back(cgmath::vec2(0.03f, 0.28f));
	positions.push_back(cgmath::vec2(-0.21f, 0.64f));
	positions.push_back(cgmath::vec2(-0.49f, 0.77f));
	positions.push_back(cgmath::vec2(-0.6f, 0.79f));
	positions.push_back(cgmath::vec2(-0.65f, 0.79f));

	positions.push_back(cgmath::vec2(-0.6f, 0.79f));
	positions.push_back(cgmath::vec2(-0.49f, 0.56f));

	positions.push_back(cgmath::vec2(-0.49f, 0.56f));//segunda punta7
	positions.push_back(cgmath::vec2(-0.58f, 0.56f));
	positions.push_back(cgmath::vec2(-0.76f, 0.52f));
	positions.push_back(cgmath::vec2(-0.84f, 0.46f));
	positions.push_back(cgmath::vec2(-0.93f, 0.38f));
	positions.push_back(cgmath::vec2(-0.94f, 0.36f));

	positions.push_back(cgmath::vec2(-0.94f, 0.36f));
	positions.push_back(cgmath::vec2(-0.7f, 0.34f));

	positions.push_back(cgmath::vec2(-0.7f, 0.34f)); //tercer punta
	positions.push_back(cgmath::vec2(-0.9f, 0.20f));
	positions.push_back(cgmath::vec2(-0.98f, 0.0f));
	positions.push_back(cgmath::vec2(-0.98f, -0.03f));


	positions.push_back(cgmath::vec2(-0.98f, -0.03f)); 
	positions.push_back(cgmath::vec2(-0.94f, 0.025f));
	positions.push_back(cgmath::vec2(-0.79f, 0.04f));

	positions.push_back(cgmath::vec2(-0.79f, 0.04f)); //cuarta punta
	positions.push_back(cgmath::vec2(-0.84f, -0.037f));
	positions.push_back(cgmath::vec2(-0.87f, -0.11f));
	positions.push_back(cgmath::vec2(-0.88f, -0.16f));
	positions.push_back(cgmath::vec2(-0.88f, -0.28f));

	positions.push_back(cgmath::vec2(-0.88f, -0.28f));
	positions.push_back(cgmath::vec2(-0.75f, -0.2f));

	positions.push_back(cgmath::vec2(-0.75f, -0.2f)); //quinta punta
	positions.push_back(cgmath::vec2(-0.79f, -0.245f));
	positions.push_back(cgmath::vec2(-0.795f, -0.385f));
	positions.push_back(cgmath::vec2(-0.76f, -0.42f));

	positions.push_back(cgmath::vec2(-0.76f, -0.42f));
	positions.push_back(cgmath::vec2(-0.73f, -0.36f));
	positions.push_back(cgmath::vec2(-0.66f, -0.31f));
	positions.push_back(cgmath::vec2(-0.60f, -0.31f));
	positions.push_back(cgmath::vec2(-0.58f, -0.34f));
	positions.push_back(cgmath::vec2(-0.58f, -0.34f));

	return positions;

}

std::vector<cgmath::vec2> schene_chaikin::createCabelloDerecho(){

	std::vector<cgmath::vec2> positions;
	
	positions.push_back(cgmath::vec2(0.13f, 0.18f));
	positions.push_back(cgmath::vec2(0.13f, 0.18f)); //primer punta
	positions.push_back(cgmath::vec2(0.15f, 0.28f));
	positions.push_back(cgmath::vec2(0.30f, 0.71f));
	positions.push_back(cgmath::vec2(0.54f, 0.80f));

	positions.push_back(cgmath::vec2(0.54f, 0.80f));
	positions.push_back(cgmath::vec2(0.42f, 0.58f));

	positions.push_back(cgmath::vec2(0.42f, 0.58f)); //segunda punta
	positions.push_back(cgmath::vec2(0.47f, 0.63f));
	positions.push_back(cgmath::vec2(0.79f, 0.68f));
	positions.push_back(cgmath::vec2(0.9f, 0.64f));

	positions.push_back(cgmath::vec2(0.9f, 0.64f));
	positions.push_back(cgmath::vec2(0.68f, 0.38f));

	positions.push_back(cgmath::vec2(0.68f, 0.38f)); //tercera punta
	positions.push_back(cgmath::vec2(0.8f, 0.36f));
	positions.push_back(cgmath::vec2(0.92f, 0.31f));
	positions.push_back(cgmath::vec2(0.98f, 0.26f));

	positions.push_back(cgmath::vec2(0.98f, 0.26f));
	positions.push_back(cgmath::vec2(0.88f, 0.26f));
	positions.push_back(cgmath::vec2(0.78f, 0.14f));

	positions.push_back(cgmath::vec2(0.78f, 0.14f)); //cuarta punta
	positions.push_back(cgmath::vec2(0.87f, 0.12f));
	positions.push_back(cgmath::vec2(0.95f, 0.05f));

	positions.push_back(cgmath::vec2(0.95f, 0.05f));
	positions.push_back(cgmath::vec2(0.78f, 0.08f));
	positions.push_back(cgmath::vec2(0.7f, -0.03f));
	positions.push_back(cgmath::vec2(0.7f, -0.03f));

	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createOrejaIzquierdo() {

	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(-0.58f, -0.34f));
	positions.push_back(cgmath::vec2(-0.58f, -0.34f));
	positions.push_back(cgmath::vec2(-0.645f, -0.331f));
	positions.push_back(cgmath::vec2(-0.67f, -0.41f));
	positions.push_back(cgmath::vec2(-0.59f, -0.45f)); 
	positions.push_back(cgmath::vec2(-0.55, -0.41f));
	positions.push_back(cgmath::vec2(-0.56, -0.4f));
	positions.push_back(cgmath::vec2(-0.56, -0.4f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createOrejaDerecho() {

	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(0.7f, -0.03f));
	positions.push_back(cgmath::vec2(0.7f, -0.03f));
	positions.push_back(cgmath::vec2(0.73f, -0.014f));
	positions.push_back(cgmath::vec2(0.78f, -0.01f));
	positions.push_back(cgmath::vec2(0.80f, -0.098f));
	positions.push_back(cgmath::vec2(0.73f, -0.12f));
	positions.push_back(cgmath::vec2(0.7, -0.09f));
	positions.push_back(cgmath::vec2(0.7, -0.09f));
	return positions;

}

std::vector<cgmath::vec2> schene_chaikin::createCabezaInferior()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(-0.56f, -0.4f));
	positions.push_back(cgmath::vec2(-0.56f, -0.4f));
	positions.push_back(cgmath::vec2(-0.56, -0.4f));
	positions.push_back(cgmath::vec2(-0.4, -0.39f));
	positions.push_back(cgmath::vec2(-0.15, -0.35f));
	positions.push_back(cgmath::vec2(-0.06, -0.34f));
	positions.push_back(cgmath::vec2(0.03f, -0.32f));
	positions.push_back(cgmath::vec2(0.03f, -0.32f)); //cuello
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createCabezaInferior_B()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(0.14f, -0.31f));
	positions.push_back(cgmath::vec2(0.14f, -0.31f));
	positions.push_back(cgmath::vec2(0.21, -0.28f));
	positions.push_back(cgmath::vec2(0.66, -0.13f));
	positions.push_back(cgmath::vec2(0.7, -0.09f));
	positions.push_back(cgmath::vec2(0.7, -0.09f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createCabezaSuperior_B()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(-0.48f, -0.18f));
	positions.push_back(cgmath::vec2(-0.48f, -0.18f));
	positions.push_back(cgmath::vec2(-0.58f, -0.34f));
	positions.push_back(cgmath::vec2(-0.58f, -0.34f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createCabezaSuperior()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(0.7f, -0.03f));
	positions.push_back(cgmath::vec2(0.7f, -0.03f));
	positions.push_back(cgmath::vec2(0.58f, 0.06f));
	positions.push_back(cgmath::vec2(0.37, 0.16f));
	positions.push_back(cgmath::vec2(0.04, 0.18f));
	positions.push_back(cgmath::vec2(-0.29f, 0.06f));
	positions.push_back(cgmath::vec2(-0.4f, -0.05f));	
	positions.push_back(cgmath::vec2(-0.4f, -0.05f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createCuello()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(0.01f, -0.32f));
	positions.push_back(cgmath::vec2(0.09f, -0.47f));
	positions.push_back(cgmath::vec2(0.14f, -0.43f));
	positions.push_back(cgmath::vec2(0.14f, -0.31f));
	positions.push_back(cgmath::vec2(0.14f, -0.31f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createGorroSuperior()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(0.12f, 0.28f));
	positions.push_back(cgmath::vec2(0.12f, 0.28f));
	positions.push_back(cgmath::vec2(0.12f, 0.32f));
	positions.push_back(cgmath::vec2(0.07f, 0.32f));
	positions.push_back(cgmath::vec2(0.07f, 0.28f));
	positions.push_back(cgmath::vec2(0.07f, 0.28f));
	return positions;

}

std::vector<cgmath::vec2> schene_chaikin::createGorro()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(0.14f, 0.25f));
	positions.push_back(cgmath::vec2(0.14f, 0.25f));
	positions.push_back(cgmath::vec2(0.10f, 0.29f));
	positions.push_back(cgmath::vec2(-0.01f, 0.26f));
	positions.push_back(cgmath::vec2(-0.03f, 0.22f));
	positions.push_back(cgmath::vec2(-0.03f, 0.19f));
	positions.push_back(cgmath::vec2(-0.03f, 0.19f)); 
	positions.push_back(cgmath::vec2(-0.04f, 0.19f));
	positions.push_back(cgmath::vec2(-0.09f, 0.14f));
	positions.push_back(cgmath::vec2(-0.09f, 0.13f));
	positions.push_back(cgmath::vec2(-0.09f, 0.13f));
	return positions;

}

std::vector<cgmath::vec2> schene_chaikin::createGorro_centro()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(-0.03f, 0.19f));
	positions.push_back(cgmath::vec2(-0.03f, 0.19f));
	positions.push_back(cgmath::vec2(0.018f, 0.21f));
	positions.push_back(cgmath::vec2(0.13f, 0.18f));
	positions.push_back(cgmath::vec2(0.13f, 0.18f));
	return positions;

}

std::vector<cgmath::vec2> schene_chaikin::createOjoIzquierdo()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(-0.4f, -0.05f));
	positions.push_back(cgmath::vec2(-0.4f, -0.05f));
	positions.push_back(cgmath::vec2(-0.46f, -0.06f));
	positions.push_back(cgmath::vec2(-0.5f, -0.2f));
	positions.push_back(cgmath::vec2(-0.37f, -0.25f));
	positions.push_back(cgmath::vec2(-0.24f, -0.15f));
	positions.push_back(cgmath::vec2(-0.27f, -0.04f));
	positions.push_back(cgmath::vec2(-0.34f, -0.04f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createOjoDerecho()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(0.16f, 0.12f));
	positions.push_back(cgmath::vec2(0.16f, 0.12f));
	positions.push_back(cgmath::vec2(0.10f, 0.07f));
	positions.push_back(cgmath::vec2(0.10f, -0.005f));
	positions.push_back(cgmath::vec2(0.20f, -0.07f));
	positions.push_back(cgmath::vec2(0.365f, -0.005f));
	positions.push_back(cgmath::vec2(0.35f, 0.10f));
	positions.push_back(cgmath::vec2(0.28f, 0.14f));
	positions.push_back(cgmath::vec2(0.28f, 0.14f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createNariz()
{
	std::vector<cgmath::vec2> positions;

	positions.push_back(cgmath::vec2(-0.1f, 0.0f));
	positions.push_back(cgmath::vec2(-0.17f, 0.0f));
	positions.push_back(cgmath::vec2(-0.24f, -0.12f));
	positions.push_back(cgmath::vec2(-0.21f, -0.21f));
	positions.push_back(cgmath::vec2(-0.12f, -0.24f));
	positions.push_back(cgmath::vec2(-0.08f, -0.23f));
	positions.push_back(cgmath::vec2(-0.08f, -0.23f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createLineaOjoIzquierdo()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(-0.48f, -0.17f));
	positions.push_back(cgmath::vec2(-0.48f, -0.17f));
	positions.push_back(cgmath::vec2(-0.39f, -0.11f));
	positions.push_back(cgmath::vec2(-0.26f, -0.09f));
	positions.push_back(cgmath::vec2(-0.26f, -0.09f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createLineaOjoDerecho()
{
	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(0.10f, 0.04f));
	positions.push_back(cgmath::vec2(0.10f, 0.04f));
	positions.push_back(cgmath::vec2(0.2, 0.07f));
	positions.push_back(cgmath::vec2(0.26f, 0.08f)); //linea ojo
	positions.push_back(cgmath::vec2(0.34f, 0.08f));
	positions.push_back(cgmath::vec2(0.34f, 0.08f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createBoca(){

	std::vector<cgmath::vec2> positions;
	positions.push_back(cgmath::vec2(0.26, -0.18f));
	positions.push_back(cgmath::vec2(0.29, -0.17f));
	positions.push_back(cgmath::vec2(0.36f, -0.10f));
	positions.push_back(cgmath::vec2(0.37f, -0.08f));
	return positions;
}

std::vector<cgmath::vec2> schene_chaikin::createPupila(int i) {
	
	std::vector<cgmath::vec2> positions;
	//izquierda
	if (i == 0) positions.push_back(cgmath::vec2(-0.4f, -0.18));
	//derecha
	else if (i == 1)  positions.push_back(cgmath::vec2(0.21f, -0.01f));
	return positions;
}

void schene_chaikin::linesFigure()
{
	//Pelo Izquierdo
	positions.push_back(createCabelloIzquierdo());
	//Pelo Derecho
	positions.push_back(createCabelloDerecho());
	//Oreja Izquierda
	positions.push_back(createOrejaIzquierdo());
	//Oreja Derecha
	positions.push_back(createOrejaDerecho());
	//Cara superior
	positions.push_back(createCabezaSuperior());
	positions.push_back(createCabezaSuperior_B());
	// Cara Inferior
	positions.push_back(createCabezaInferior());
	positions.push_back(createCabezaInferior_B());
	//Cuello
	positions.push_back(createCuello());
	//Gorro
	positions.push_back(createGorro());
	positions.push_back(createGorroSuperior());
	positions.push_back(createGorro_centro());
	//Ojo izquierdo
	positions.push_back(createOjoIzquierdo());
	positions.push_back(createLineaOjoIzquierdo());
	//Ojo Derecha */
	positions.push_back(createOjoDerecho());
	positions.push_back(createLineaOjoDerecho());
	//Nariz
	positions.push_back(createNariz());
	//Boca
	positions.push_back(createBoca());
	//Pupila Izquierda
	positions.push_back(createPupila(0));
	//Pupila Derecha
	positions.push_back(createPupila(1));
}

void schene_chaikin::lineStripFigure()
{
	//Pelo Izquierdo
	positions.push_back(schene_chaikin::calculate_chaikin(createCabelloIzquierdo()));
	//Pelo Derecho
	positions.push_back(schene_chaikin::calculate_chaikin(createCabelloDerecho()));
	//Oreja Izquierda
	positions.push_back(schene_chaikin::calculate_chaikin(createOrejaIzquierdo()));
	//Oreja Derecha
	positions.push_back(schene_chaikin::calculate_chaikin(createOrejaDerecho()));
	//Cara superior
	positions.push_back(schene_chaikin::calculate_chaikin(createCabezaSuperior()));
	positions.push_back(schene_chaikin::calculate_chaikin(createCabezaSuperior_B()));
	// Cara Inferior
	positions.push_back(schene_chaikin::calculate_chaikin(createCabezaInferior()));
	positions.push_back(schene_chaikin::calculate_chaikin(createCabezaInferior_B()));
	//Cuello
	positions.push_back(createCuello());
	// Gorro
	positions.push_back(schene_chaikin::calculate_chaikin(createGorro()));
	positions.push_back(schene_chaikin::calculate_chaikin(createGorroSuperior()));
	positions.push_back(schene_chaikin::calculate_chaikin(createGorro_centro()));
	//Ojo izquierdo */
	positions.push_back(schene_chaikin::calculate_chaikin(createOjoIzquierdo()));
	positions.push_back(schene_chaikin::calculate_chaikin(createLineaOjoIzquierdo()));
	//Ojo Derecha */
	positions.push_back(schene_chaikin::calculate_chaikin(createOjoDerecho()));
	positions.push_back(schene_chaikin::calculate_chaikin(createLineaOjoDerecho()));
	//Nariz
	positions.push_back(schene_chaikin::calculate_chaikin(createNariz()));
	//Boca
	positions.push_back(schene_chaikin::calculate_chaikin(createBoca()));
	//Pupila Izquierda
	positions.push_back(createPupila(0));
	//Pupila Derecha
	positions.push_back(createPupila(1));
}

void schene_chaikin::normalKeysDown(unsigned char key)
{
	if (key == '1') displayLines = !displayLines;
	if (key == '2') displayLineStrip = !displayLineStrip;
}