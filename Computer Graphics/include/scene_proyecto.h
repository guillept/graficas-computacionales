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
	float radians(float grados);
	cgmath::mat4 rotateX(float iTime);
	cgmath::mat4 rotateY(float iTime);
	cgmath::mat4 rotateZ(float iTime);
	cgmath::mat4 scaleM();
	cgmath::mat4 translation(float x, float y, float z);
	cgmath::mat4 identidad();
	cgmath::mat4 projection();
	void setColors();
	void initParticulas();
	void resetParticula(int i);
	float random(float fMax, float fMin);
	void moverGota(int i);
	void draw();

private:
	GLuint shader_program;
	GLuint vao;
	GLuint positionsVBO, colorsVBO, mxpMatrixVBO, indicesBuffer, texturasVBO;

	GLfloat x = 3.f, y = 3.f, z = 3.f, aspect = 1.0f;

	int minimoNumeroVertices = 4;

	cgmath::mat4 rotX, rotY, rotZ, scale, trans, transCamara;
	cgmath::mat4 Projection, View, Model, matrizDeCamara;
	cgmath::mat4 mxpMatrix;
	cgmath::vec3 moverCamara;

	std::vector<cgmath::vec4> positions;
	std::vector<cgmath::vec3> colors;
	std::vector<cgmath::vec2> textura;

	ILuint imageID;
	GLuint textureId;


	/*std::vector<float> life; // vida
	std::vector<float> fade; // fade
	float	r, g, b;    // color
	std::vector<cgmath::vec3> particulas; // posicion
	std::vector<cgmath::vec3> veclocidad; // velocidad 
	// std::vector<cgmath::vec3> aceleracion; // aceleracion
	*/
	std::vector<float> life; // vida
	std::vector<float> fade; // fade
	float	r, g, b;    // color
	std::vector<cgmath::vec3> particulas; // posicion
	std::vector<cgmath::vec3> veclocidad; // velocidad
	// std::vector<cgmath::vec3> aceleracion; // aceleracion
	float aceleracion = .00981f;
	float bound = 35.f;
	float lifeLowerBound = 500, lifeUpperBound = 1000, lifeTime;
};