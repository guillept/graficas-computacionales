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

class scene_fuego : public scene
{
public:
	~scene_fuego();

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
	void createNormales();
	void first_render();
	void second_render();
	void createFloor();

	// FUNCIONES AUXILIARES
	void setXYZ();


private:
	GLuint shader_program_depth, shader_program_shadow;
	GLuint vao, vaoWall;

	// Particles
	GLuint positionsVBO, colorsVBO, mxpMatrixVBO, indicesBuffer, texturasVBO, normalsVBO;
	std::vector<GLfloat> lifes;
	std::vector<cgmath::vec4> positions;
	std::vector<cgmath::vec3> veclocidad, normals, aceleracion, posicionesParticulaOrigen; // posicion original de la particula
	std::vector<cgmath::vec2> textura;
	std::vector<float> born;
	GLfloat gravedad = 9.81f, bound = 80.f, upperBound = 100.f, lifeTime = 300, wind = 0, maxAceleracion = 5;

	struct Particula {
		int position;
		cgmath::vec3 distance;
		bool operator<(Particula& that) {
			return this->distance.magnitude() > that.distance.magnitude();
		};
	} particulas[MAX_PARTICULAS];

	// Camara
	cgmath::mat4 trans;
	cgmath::mat4 Projection, View, Model, matrizDeCamara, ViewModel, mxpMatrix;
	cgmath::vec3 moverCamara;

	// Luz
	cgmath::mat4 camaraLuz;
	cgmath::mat4 ViewLuz, OrtoProj, LightVPMatrix;

	// Texturas
	ILuint imageID, floorId;
	GLuint textureId, textureFloorId;

	// Wall
	GLuint wallNormalsVBO, indicesWallBuffer, wallVBO, texturasWallVBO;
	std::vector<cgmath::vec3> wallPositions, wallNormals;
	std::vector<cgmath::vec2> texturaWall;
	cgmath::mat4 ModelWall, mxpWallMatrix;
	GLfloat xFloor = 80, zFloor = 0, yFloor = 80;

	// Pool
	GLint willPartiTheParticleLive, particulasPorFrame = 100, rem = 0;

	//Auxiliary variables
	GLfloat x, y, z, aspect = 1.0f;
	GLint index;
	GLint width = 400, height = 400;

	depth_buffer depthBuffer;
};
