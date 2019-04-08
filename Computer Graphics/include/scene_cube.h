#pragma once

#include "scene.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"

// Escena de prueba para comenzar a trabajar con
// fragment shaders.
class scene_cube : public scene
{
public:
	~scene_cube();

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
	float radians(float grados);

private:
	GLuint shader_program;
	GLuint vao;
	GLuint positionsVBO, colorsVBO, mxpMatrixVBO, indicesBuffer;

	GLfloat x = 3.f, y = 3.f, z = 3.f, aspect = 1.0f;

	int minimoNumeroVertices = 4;

	cgmath::mat4 rotX, rotY, rotZ, scale, trans;
	cgmath::mat4 Projection, View, Model;
	cgmath::mat4 mxpMatrix;
};