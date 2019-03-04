/* #include <iostream>

OLD OPEN GL

#include "complex.h" //busca en carpeta include
#include "time.h"


/*Siempre que quieran utiliazr OpenGl se deben incluir en este orden
#include <GL/glew.h>
#include <GL/freeglut.h>
float angle = 0.0f;
void render_loop() 
{
	time::tick();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(sin(time::elapsed_time().count()), 1.0f, 0.5f, 1.0f); anima el color del fondo

	//WARNING
	//OpenGl viejo

	glRotatef(/*1.0f * time::delta_time().count() angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES); //figuras seran triangulos
	glColor3f(1.0f, 0.0f, 0.0f); //Red
	glVertex2f(-1.0f, -1.0f); //vertivces se envian a la tarjeta de video
	glColor3f(0.0f, 0.0f, 1.0f); //Green
	glVertex2f(1.0f, -1.0f); //vertivces se envian a la tarjeta de video
	glColor3f(0.0f, 1.0f, 0.0f); //Blue
	glVertex2f(0.0f, 1.0f); //vertivces se envian a la tarjeta de video
	
	glEnd();


	glPopMatrix();
	angle += 1.0f; //rotan fuera de un for
	
	glutSwapBuffers();

	//WARNING


	//OpenGl entra en estado de espera
}

void idle()
{
	/*Cuando OpenGL está en un estado de espera, vuelve a dibujar 
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{

	/* 
	Clase 3
	cgmath::complex c; //instanciado objeto de tipo complex. Constructor de default
	cgmath::complex c2(1.0f, 2.0f);

	/* c.print();
	c2.print();

	std::cout << c;
	std::cout << c2;

	c.add(c2);
	std::cout << c;

	c += c2;
	std::cout << c;

	cgmath::complex c3  = cgmath::complex::add(c, c2);

	std::cout << c3;


	std::cout << c + c2 + c3 << std::endl;

	std::cout << "Press Enter" << std::endl;
	std::cin.get(); //abrir consola y pedir enter 

	/*Freeflut se usa para abrir ventanas y configurar el contexto de OpenGl
	glutInit(&argc, argv);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); //Inicilizar tiempo
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS) ;
	glutInitWindowSize(400, 400); //Inicializa la ventana
	glutInitDisplayMode(GLUT_RGBA| GLUT_DEPTH | GLUT_DOUBLE); //Framebuffer, double buffer para escribir en uno mientras se muestra el otro
	glutCreateWindow("Hello World");
	glutDisplayFunc(render_loop); //Cada frame que suceda se llama esta funcion
	glutIdleFunc(idle);

	/*Incializar GLEW -> busca el API de OpenGl directamente en la tarketa de video
	Microsoft no lo exopne directamente
	glewInit();

	//cONFIGURAR oPENgL
	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); //culling, cara delantera.
	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);//valor por fefault cuando es borre la memoria 

	std::cout << glGetString(GL_VERSION) << std::endl; //Mostrar la version de OpenGl con la que trabajamos

	time::init();

	/* Loop Infinito (render loop) -> freeGlut llama el MainLOOP, termina cuando se cierra la ventana
	Se pausa la ejecucion del main
	glutMainLoop();
	return 0;
}

*/

#include "scene_manager.h"


int main(int argc, char* argv[])
{

	scene_manager::start(argc, argv, "Hello, World!", 400, 400);

	return 0;
}