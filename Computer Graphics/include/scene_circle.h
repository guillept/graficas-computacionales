#pragma once

#include "scene.h"

// Escena de prueba para comenzar a trabajar con
// fragment shaders.
class scene_circle : public scene
{
public:
	~scene_circle();

	void init();
	void awake();
	void sleep();
	void reset() { }
	void mainLoop();
	void resize(int width, int height);
	void normalKeysDown(unsigned char key) { }
	void normalKeysUp(unsigned char key) { }
	void specialKeys(int key) { }
	void passiveMotion(int x, int y) { }

private:
	GLuint shader_program;

	GLuint vao;
	GLuint positionsVBO, colorsVBO;
	GLuint indicesBuffer;

	const int TOTAL_SIDES = 360;
	const int TOTAL_VERTICES = 362;
	const float radius = 1.0f;
};