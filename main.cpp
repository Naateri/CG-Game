#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <fcntl.h> //opening device
#include <unistd.h> //read
#include <linux/joystick.h>
#include "Controller.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;

struct js_event e;
int fd;

struct Point{
	int x,y;
	Point(int x, int y){
		this->x = x; this->y = y;
	}
	void draw(){
		glPointSize(10);
		glBegin(GL_POINTS);
		glVertex2f(x,y);
		glEnd();
	}
};

Point* particle = new Point(0,0);
int difference = 20;

void move(){
	/*if (e.value == -32767 && e.number == 6){
	particle->x -= difference;
} else if (e.value == 32767 && e.number == 6){
	particle->x += difference;
} else if (e.value == -32767 && e.number == 7){
	particle->y += difference;
} else if (e.value == 32767 && e.number == 7){
	particle->y -= difference;
}*/
	if (e.value > 0 && e.number == 14){
		particle->y -= difference;
	} else if (e.value >0 && e.number == 13){
		particle->y += difference;
	} else if (e.value >0 && e.number == 16){
		particle->x += difference;
	} else if (e.value >0 && e.number == 15){
		particle->x -= difference;
	}
	
	///PS3:
	//X: 0
	//O: 1
	//Triangle: 2
	//Square: 3
}

void displayGizmo(){
	glBegin(GL_LINES);
	glEnable(GL_PROGRAM_POINT_SIZE);
	/*glColor3d(255,20,47);
	glVertex2d(-300, 0);
	glVertex2d(300, 0);
	glColor3d(0, 0, 255);
	glVertex2d(0, -300);
	glVertex2d(0, 300);*/
	glEnd();
}
bool r = false;

void draw_point(int x, int y);

void OnMouseClick(int button, int state, int x, int y){
	;
}

void OnMouseMotion(int x, int y){
	if(r)
		std::cout << x-300 << " " << 300-y << std::endl;
	//opcional
	//hacer algo x,z cuando se mueve el mouse
}

void idle(){ // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

//funcion llamada a cada imagen
void glPaint(void) {
	
	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	glOrtho(-300.0f,  300.0f,-300.0f, 300.0f, -1.0f, 1.0f);
	
	//dibujar quadTree (qt->draw())
	glPointSize(3);
	glBegin(GL_POINTS);
	
	glEnd();
	
	int n = read(fd, &e, sizeof(e));
	
	printf("%d %d %d %d\n", e.value, e.number, e.type, e.time);
	
	if (e.value == 1 && e.number == 1) exit(0);
	
	//cout << (int)e.value << ' ' << (int)e.number << '\n';
	
	move();
	
	particle->draw();
	
	//dibuja el gizmo
	displayGizmo();
	
	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

void draw_point(int x, int y){
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2f(x-300,300-y);
	glEnd();
	displayGizmo();
	
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0, 0, 0, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	
	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;
		
	default:
		break;
	}
	
}
//
//el programa principal
//
int main(int argc, char** argv) {
	
	fd = open("/dev/input/js0", O_RDONLY);
	
	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("Lul"); //titulo de la ventana
	
	init_GL(); //funcion de inicializacion de OpenGL
	
	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);
	
	//qt = new quadTree();
	glutMainLoop(); //bucle de rendering
	//no escribir nada abajo de mainloop
	return 0;
}
