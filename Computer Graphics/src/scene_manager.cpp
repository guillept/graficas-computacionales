#include "scene_manager.h"

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "scene.h"
#include "scene_compatibility.h"
#include "scene_primitives.h"
#include "schene_chaikin.h"
#include "scene_conchoid.h"
#include "scene_vertex.h"
#include "scene_fragment.h"
#include "scene_circle_grid.h"
#include "scene_sphere.h"
#include "scene_circle.h"

#include "time.h"

std::vector<std::unique_ptr<scene>> scene_manager::sceneList;
int scene_manager::currentScene = -1;

void scene_manager::start(int argc, char* argv[], const std::string& name, int width, int height)
{
	// Time init
	time::init();

	// Freeglut init
	glutInit(&argc, argv);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(width, height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(name.c_str());
	glutDisplayFunc(mainLoop);
	glutIdleFunc(idle);
	glutReshapeFunc(resize);
	glutCloseFunc(cleanup);
	glutKeyboardFunc(normalKeysDown);
	glutKeyboardUpFunc(normalKeysUp);
	glutSpecialFunc(specialKeys);
	glutPassiveMotionFunc(passiveMotion);

	// Glew init
	glewExperimental = true;
	glewInit();

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// GL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Scene init
	initialize();

	// Run main loop
	glutMainLoop();
}

void scene_manager::next()
{
	int nScenes = (int)sceneList.size();
	if (nScenes > 0)
	{
		sceneList.at(currentScene)->sleep();
		currentScene = (currentScene + 1) % nScenes;
		sceneList.at(currentScene)->awake();
	}
}

void scene_manager::prev()
{
	int nScenes = (int)sceneList.size();
	if (nScenes > 0)
	{
		sceneList.at(currentScene)->sleep();
		currentScene--;
		if (currentScene < 0)
			currentScene = (nScenes - 1);
		sceneList.at(currentScene)->awake();
	}
}

void scene_manager::initialize()
{
	// Ejemplo de como agregar escenas al proyecto
	//std::unique_ptr<scene> somescene(new scene_project);
	//sceneList.push_back(std::move(somescene));
	
	/* std::unique_ptr<scene> scene1(new scene_compatibility);
	sceneList.push_back(std::move(scene1));

	std::unique_ptr<scene> scene2(new scene_primitives);
	sceneList.push_back(std::move(scene2));  

	std::unique_ptr<scene> scene_conchoid(new scene_conchoid);
	sceneList.push_back(std::move(scene_conchoid)); 

	std::unique_ptr<scene> schene_chaikin(new schene_chaikin);
	sceneList.push_back(std::move(schene_chaikin)); 

	std::unique_ptr<scene> scene_vertex(new scene_vertex);
	sceneList.push_back(std::move(scene_vertex));

	std::unique_ptr<scene> scene_fragment(new scene_fragment);
	sceneList.push_back(std::move(scene_fragment)); */

	/*std::unique_ptr<scene> scene_circle_grid(new scene_circle_grid);
	sceneList.push_back(std::move(scene_circle_grid));

	std::unique_ptr<scene> scene_sphere(new scene_sphere);
	sceneList.push_back(std::move(scene_sphere)); */

	std::unique_ptr<scene> scene_circle(new scene_circle);
	sceneList.push_back(std::move(scene_circle));
	
	
	for (auto& s : sceneList)
		s->init();

	if (sceneList.size() > 0)
	{
		currentScene = 0;
		sceneList.at(currentScene)->awake();
	}
}

void scene_manager::mainLoop()
{
	time::tick();

	if (currentScene >= 0)
		sceneList.at(currentScene)->mainLoop();

	glutSwapBuffers();
}

void scene_manager::idle()
{
	glutPostRedisplay();
}

void scene_manager::cleanup()
{
	sceneList.clear();
	currentScene = -1;
}

void scene_manager::resize(int width, int height)
{
	if (currentScene >= 0)
		sceneList.at(currentScene)->resize(width, height);
}

void scene_manager::normalKeysDown(unsigned char key, int x, int y)
{
	if (key == '+')
		next();

	if (key == '-')
		prev();

	if (key == 'r')
		if (currentScene >= 0)
			sceneList.at(currentScene)->reset();

	if (currentScene >= 0)
		sceneList.at(currentScene)->normalKeysDown(key);
}

void scene_manager::normalKeysUp(unsigned char key, int x, int y)
{
	if (currentScene >= 0)
		sceneList.at(currentScene)->normalKeysUp(key);
}

void scene_manager::specialKeys(int key, int x, int y)
{
	if (currentScene >= 0)
		sceneList.at(currentScene)->specialKeys(key);
}

void scene_manager::passiveMotion(int x, int y)
{
	if (currentScene >= 0)
		sceneList.at(currentScene)->passiveMotion(x, y);
}