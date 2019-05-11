#pragma once

#include "scene.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"

#include <vector>
#include <IL/il.h>

#include "depth_buffer.h"

#define MAX_PARTICULAS 1000

class scene_lluvia : public scene
{
public:
	~scene_lluvia();

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

	// OPERACIONES DE MATRICES
	cgmath::mat4 rotateX(GLfloat iTime);
	cgmath::mat4 rotateY(GLfloat iTime);
	cgmath::mat4 rotateZ(GLfloat iTime);
	cgmath::mat4 translation(GLfloat x, GLfloat y, GLfloat z);
	cgmath::mat4 projection();
	cgmath::mat4 camera(cgmath::vec3 camara);
	cgmath::mat4 ortographicProjection();
	void billboard(cgmath::mat4 view);

	// OPERACIONES MATEMÁTICAS
	GLfloat radians(GLfloat grados);
	GLfloat random(GLfloat fMax, GLfloat fMin);
	cgmath::vec3 calculateDistance(int i);

	// CONTROLAR LAS PARTICULAS
	void initParticulas();
	void setTexturas();
	void resetParticula(int i);
	void createParticalesVao();
	void createFloorVao();
	void createNormales();
	void first_render();
	void second_render();
	void createFloor();

	// FUNCIONES AUXILIARES
	void setXYZ();


private:
	GLuint shader_program_depth, shader_program_shadow;
	GLuint vao, vaoFloor;

	// Particles
	GLuint positionsVBO, colorsVBO, mxpMatrixVBO, indicesBuffer, texturasVBO, normalsVBO;

	cgmath::mat4 trans;
	cgmath::mat4 Projection, View, Model, matrizDeCamara, ViewModel, mxpMatrix;
	cgmath::vec3 moverCamara;

	cgmath::mat4 camaraLuz;
	cgmath::mat4 ViewLuz, OrtoProj, LightVPMatrix;

	ILuint imageID, floorId;
	GLuint textureId, textureFloorId;

	std::vector<GLfloat> lifes;
	std::vector<cgmath::vec4> positions;
	std::vector<cgmath::vec3> veclocidad;
	std::vector<cgmath::vec3> posicionesParticulaOrigen; // posicion original de la particula
	std::vector<cgmath::vec2> textura;

	// Floor
	GLuint  floorNormalsVBO, indicesFloorBuffer, floorVBO, texturasFloorVBO, floorNormlasVBO;
	std::vector<cgmath::vec3> floor, floorPosition;
	std::vector<cgmath::vec3> normals, floorNormals;
	std::vector<cgmath::vec2> texturaFloor;

	cgmath::mat4 ModelFloor, mxpFloorMatrix;

	struct Particula {
		int position;
		cgmath::vec3 distance;
		bool operator<(Particula& that) {
			return this->distance.magnitude() > that.distance.magnitude();
		};
	} particulas[MAX_PARTICULAS];

	GLfloat aceleracion = 9.81f, bound = 80.f, upperBound = 100.f, lifeTime = 800, wind = 0;

	//Auxiliary variables
	GLfloat x, y, z, willPartiTheParticleLive, aspect = 1.0f;
	int index;
	GLfloat xFloor = 80, zFloor = 0, yFloor = 80;

	depth_buffer depthBuffer;
};
