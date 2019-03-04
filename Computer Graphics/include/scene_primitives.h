#pragma once

#include "scene.h"

class scene_primitives : public scene
{
public:
	void init();
	void awake();
	void sleep();
	void reset() {}
	void mainLoop();
	void resize(int width, int height){}
	void normalKeysDown(unsigned char key);
	void normalKeysUp(unsigned char key) {}
	void specialKeys(int key) {}
	void passiveMotion(int x, int y) {}

private:

	//Este es el manager de memoria
	GLuint vao;

	//Buffer con atributo
	GLuint positionsVBO;

	GLenum primitiveType;
};