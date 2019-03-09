#pragma once

#include "scene.h"
#include "vec2.h"
#include <vector>

class schene_chaikin : public scene
{
public:
	void init();
	void awake();
	void sleep();
	void reset() {}
	void mainLoop();
	void resize(int width, int height) {}
	void normalKeysDown(unsigned char key);
	void normalKeysUp(unsigned char key) {}
	void specialKeys(int key) {}
	void passiveMotion(int x, int y) {}

	std::vector<cgmath::vec2> calculate_chaikin(std::vector<cgmath::vec2> positions);
	void createVao(int i, std::vector<cgmath::vec2> position);
	std::vector<cgmath::vec2> createCabelloIzquierdo();
	std::vector<cgmath::vec2> createCabelloDerecho();
	std::vector<cgmath::vec2> createOrejaIzquierdo();
	std::vector<cgmath::vec2> createOrejaDerecho();
	std::vector<cgmath::vec2> createCabezaInferior();
	std::vector<cgmath::vec2> createCabezaInferior_B();
	std::vector<cgmath::vec2> createCabezaSuperior();
	std::vector<cgmath::vec2> createCabezaSuperior_B();
	std::vector<cgmath::vec2> createCuello();
	std::vector<cgmath::vec2> createGorro();
	std::vector<cgmath::vec2> createGorro_centro();
	std::vector<cgmath::vec2> createOjoIzquierdo();
	std::vector<cgmath::vec2> createOjoDerecho();
	std::vector<cgmath::vec2> createLineaOjoIzquierdo();
	std::vector<cgmath::vec2> createLineaOjoDerecho();
	std::vector<cgmath::vec2> createBoca();
	std::vector<cgmath::vec2> createNariz();
	std::vector<cgmath::vec2> createPupila(int i);
	std::vector<cgmath::vec2> createGorroSuperior();
	void lineStripFigure();
	void linesFigure();
	void draw(int i, GLenum primitiveType);

private:

	//Este es el manager de memoria
	GLuint vaos[100];

	//Buffer con atributo
	GLuint positionsVBO;
	GLfloat Qx, Rx, Qy, Ry;

	std::vector<std::vector<cgmath::vec2>> positions;
	bool displayLines = true, displayLineStrip = true;
	
};