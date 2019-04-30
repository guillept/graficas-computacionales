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

// Escena de prueba para comenzar a trabajar con
// fragment shaders.
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
	cgmath::mat4 scaleM();
	cgmath::mat4 translation(GLfloat x, GLfloat y, GLfloat z);
	cgmath::mat4 identidad();
	cgmath::mat4 projection();
	void setXYZ();
	void setColors();
	void initParticulas();
	void resetParticula(int i);
	GLfloat random(GLfloat fMax, GLfloat fMin);
	cgmath::vec3 calculateDistance(int i);

private:
	GLuint shader_program;
	GLuint vao;
	GLuint positionsVBO, colorsVBO, mxpMatrixVBO, indicesBuffer, texturasVBO;

	GLfloat x, y, z, aspect = 1.0f;

	int minimoNumeroVertices = 4;

	cgmath::mat4 rotX, rotY, rotZ, scale, trans, transCamara;
	cgmath::mat4 Projection, View, Model, matrizDeCamara, ViewModel;
	cgmath::mat4 mxpMatrix;
	cgmath::vec3 moverCamara;

	std::vector<cgmath::vec3> posicionesParticulaOrigen; // posicion original de la particula
	std::vector<cgmath::vec3> colors;
	std::vector<cgmath::vec2> textura;

	ILuint imageID;
	GLuint textureId;

	std::vector<float> life; // vida
	std::vector<float> fade; // fade
	GLfloat	r, g, b;    // color
	std::vector<cgmath::vec4> positions;
	std::vector<cgmath::vec3> veclocidad; // velocidad
	// std::vector<int> particulas; //indexes to relate the arrays

	struct particula {
		int position;
		cgmath::vec3 distance;
		bool operator<(particula& that) {
			return this->distance.magnitude() > that.distance.magnitude();
		};
	} particulas[MAX_PARTICULAS];

	//std::vector<particula> particulas;
	GLfloat aceleracion = .000981f; //.000981f;
	GLfloat bound = 50.f;
	GLfloat lifeTime = 2000;
	GLfloat start, end;
};