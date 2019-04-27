#pragma once

#include "scene.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"

#include <vector>

#include <IL/il.h>

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
	cgmath::mat4 rotateX(float iTime);
	cgmath::mat4 rotateY(float iTime);
	cgmath::mat4 rotateZ(float iTime);
	cgmath::mat4 scaleM();
	cgmath::mat4 translation();
	cgmath::mat4 camera();
	cgmath::mat4 projection();
	void createCube();
	void setColors();

private:
	GLuint shader_program;
	GLuint vao;
	GLuint positionsVBO, colorsVBO, mxpMatrixVBO, indicesBuffer, texturasVBO;

	GLfloat x = 3.f, y = 3.f, z = 3.f, aspect = 1.0f;

	int minimoNumeroVertices = 4;

	cgmath::mat4 rotX, rotY, rotZ, scale, trans;
	cgmath::mat4 Projection, View, Model;
	cgmath::mat4 mxpMatrix;

	std::vector<cgmath::vec3> positions;
	std::vector<cgmath::vec3> colors;
	std::vector<cgmath::vec2> textura;

	ILuint imageID;
	GLuint textureId;
};