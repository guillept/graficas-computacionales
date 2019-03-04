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
	void normalKeysDown(unsigned char key) {}
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
	std::vector<cgmath::vec2> createCuello();
	// std::vector<cgmath::vec2> createCabelloIzquierdo();
private:

	//Este es el manager de memoria
	GLuint vao0, vao1, vao2, vao3, vao4, vao5, vao6, vao7;

	//Buffer con atributo
	GLuint positionsVBO, ebo;
	GLfloat Qx, Rx, Qy, Ry;

	GLuint size_0, size_1, size_2, size_3, size_4, size_5, size_6, size_7, size_8;
};