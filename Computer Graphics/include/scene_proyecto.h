#pragma once

#include "scene.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"

#include <vector>
#include <IL/il.h>

#define MAX_PARTICULAS 1000

class scene_proyecto : public scene
{
public:
	~scene_proyecto();

	void init();
	void awake();
	void sleep();
	void reset() { }
	void mainLoop();
	void resize(int width, int height);
	void normalKeysDown(unsigned char key);
	void normalKeysUp(unsigned char key) { }
	void specialKeys(int key) { }
	void passiveMotion(int x, int y) { }
	GLfloat radians(GLfloat grados);
	cgmath::mat4 rotateX(GLfloat iTime);
	cgmath::mat4 rotateY(GLfloat iTime);
	cgmath::mat4 rotateZ(GLfloat iTime);
	cgmath::mat4 translation(GLfloat x, GLfloat y, GLfloat z);
	cgmath::mat4 projection();

	//Auxiliary algorithms
	void initParticulas();
	void setTexturas();
	void resetParticula(int i);
	GLfloat random(GLfloat fMax, GLfloat fMin);
	cgmath::vec3 calculateDistance(int i);
	void billboard();
	void setXYZ();
	void setColors();

private:
	GLuint shader_program;
	GLuint vao;
	GLuint positionsVBO, colorsVBO, mxpMatrixVBO, indicesBuffer, texturasVBO;

	cgmath::mat4 trans;
	cgmath::mat4 Projection, View, Model, matrizDeCamara, ViewModel, mxpMatrix;
	cgmath::vec3 moverCamara;

	ILuint imageID;
	GLuint textureId;

	std::vector<GLfloat> lifes;
	std::vector<cgmath::vec4> positions;
	std::vector<cgmath::vec3> veclocidad;
	std::vector<cgmath::vec3> posicionesParticulaOrigen; // posicion original de la particula
	std::vector<cgmath::vec3> colors;
	std::vector<cgmath::vec2> textura;

	struct Particula {
		int position;
		cgmath::vec3 distance;
		bool operator<(Particula& that) {
			return this->distance.magnitude() > that.distance.magnitude();
		};
	} particulas[MAX_PARTICULAS];

	GLfloat aceleracion = 9.81f, bound = 80.f, lifeTime = 1000;

	//Auxiliary variables
	GLfloat x, y, z, willPartiTheParticleLive, aspect = 1.0f;
	int index;
};