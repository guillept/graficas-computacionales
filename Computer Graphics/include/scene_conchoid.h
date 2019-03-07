#pragma once

#include "scene.h"
#include "vec2.h"
#include <vector>

class scene_conchoid : public scene
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
	std::vector<cgmath::vec2> calcularConchoid(int i);
	void createVao(int i, std::vector<cgmath::vec2> position);


private:

	//Este es el manager de memoria
	GLuint vaos[2];

	//Buffer con atributo
	GLuint positionsVBO;

	std::vector<std::vector<cgmath::vec2>> positions;

	int size = 0;
};