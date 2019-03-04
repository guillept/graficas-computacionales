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

private:

	//Este es el manager de memoria
	GLuint vao, vao2;

	//Buffer con atributo
	GLuint ebo;
	GLuint positionsVBO, ebo2;
	GLfloat Qx, Rx, Qy, Ry;

	GLuint size = 0;
};