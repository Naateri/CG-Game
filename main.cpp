#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <fcntl.h> //opening device
#include <unistd.h> //read
#include <linux/joystick.h>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "Controller.h"
#include "Player.h"
#include "Enemy.h"

#include "Point.h"
#include "Meteors.h"

#define RED 0
#define GREEN 0
#define BLUE 0
#define ALPHA 1

#define MAX_TIME 120.0f
#define MAX_ENEMIES 3
#define TYPE_ENEMIES 3

using namespace std;

struct js_event e;
int fd;
PS3Controller* Controller1;
Player* p1;

Point2D* particle = new Point2D(0,0);
int difference = 20;

Enemy* enemy1;
Meteor* meteor;

std::chrono::steady_clock::time_point begin_t; //enemies
std::chrono::steady_clock::time_point end_t; //add enemies idle time
Enemy* enemy2;
Enemy* enemy3;

std::chrono::steady_clock::time_point begin_meteor;
std::chrono::steady_clock::time_point end_meteor; //add meteors idle time

std::chrono::steady_clock::time_point begin_eg; //end of game

bool player1 = false;
bool added_enemies = false;
bool added_meteors = false;
bool meteor_collision = false;

/////SAME FRAMERATE////
int time_execution=0;
int timebase=0;
////END SAME FRAMERATE///

int a = 0;

std::vector<Meteor*> meteors;

void displayGizmo(){
	glBegin(GL_LINES);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnd();
}
bool r = false;

void add_enemies(){
	if (enemies.size() >= MAX_ENEMIES) return;
	
	if (!added_enemies){
		begin_t = std::chrono::steady_clock::now();
		added_enemies = true;
	}
	end_t = std::chrono::steady_clock::now();
	
	std::chrono::duration<double> elapsed_seconds = end_t - begin_t;
	double time1 = elapsed_seconds.count();
	
	
	if (time1 >= 1.0f){
		srand(unsigned(time(0)));
		int r = (rand() % TYPE_ENEMIES) + 1;
		switch(r){
			case 1 :{
				enemy1 = new Enemy1(p1);
				enemies.push_back(enemy1);
				break;
			}
			case 2 :{
				enemy2 = new Enemy2(p1);
				enemies.push_back(enemy2);
				break;
			}
				
			case 3 :{ ///linea 34
				enemy3 = new Enemy3(p1);
				enemies.push_back(enemy3);
				break;
			}
				
		}
		
		/*enemy1 = new Enemy1;
		enemies.push_back(enemy1);*/
		added_enemies = false;
	}
}

void add_meteorite(){
	if (!added_meteors){
		begin_meteor = std::chrono::steady_clock::now();
		added_meteors = true;
	}
	end_meteor = std::chrono::steady_clock::now();
	
	std::chrono::duration<double> elapsed_seconds = end_meteor - begin_meteor;
	double time = elapsed_seconds.count();
	
	if (time >= 5.0f){
		cout << "Meteorite spawning\n";
		meteor = new Meteor(p1);
		meteors.push_back(meteor);
		added_meteors = false;
	}
}

void kill_player(){
	std::chrono::steady_clock::time_point end_eg = std::chrono::steady_clock::now(); //end of game
	std::chrono::duration<double> elapsed_seconds = end_meteor - begin_meteor;
	double time = elapsed_seconds.count();
	
	if (time >= 4.0f){
		p1->kill_player();
	}
}

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity();
	//glOrtho(-300.0f,  300.0f,-300.0f, 300.0f, -1.0f, 1.0f);
	/// Esto fue lo que cambié jijiji
	gluPerspective(45.0, 1.0, 1.0, 500.0);
	
	
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode (GL_BACK, GL_LINE);
	
	glTranslatef(0, 0, -300.0);
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	
	
	glPopMatrix();
	
	
	//particle->draw();
	
	time_execution = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
	float dt = float(time_execution -timebase)/1000.0;// delta time
	timebase = time_execution;
	
	add_enemies();
	add_meteorite();
	
	a += 10 * dt;
	if (!player1){
		thread t1(&Player::move, p1);
		player1 = true;
		t1.detach();
	}
	//move();
	//p->move();
	p1->draw();
	
	
	
	for(int i = 0; i < enemies.size(); i++){
		enemies[i]->move();
		enemies[i]->draw();
	}
	
	for(int i = 0; i< items.size();i++){
		items[i]->move();
		items[i]->draw();
		
		
	}
	for(int i = 0; i < meteors.size(); i++){
		meteors[i]->move();
		meteors[i]->draw();
		if (meteors[i]->player_collision()) meteor_collision= true;
	}
	
	//enemy1->draw();
	//dibuja el gizmo
	displayGizmo();
	
	if (meteor_collision){
		enemies.clear();
		meteors.clear();
		//delete p1;
		begin_eg = std::chrono::steady_clock::now();
		kill_player();
	}
	
	if (p1->time_passed() >= MAX_TIME || !p1->is_alive()){
		std::cout << "Game over\n";
		delete p1;
		exit(0);
	}
	
	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
	glFlush();
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
	//glClearColor(0, 0, 0, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_COLOR_MATERIAL);
	//modo projeccion
	//glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	glutSwapBuffers();
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

GLvoid initGL()
{
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

}
//
//el programa principal
//
int main(int argc, char** argv) {
	
	Controller1 = new PS3Controller("/dev/input/js2");
	Controller1->open_fd();
	cout << "Controller opened\n";
	
	p1 = new Player(Controller1);
	
	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("Chicken Invaders"); //titulo de la ventana
	
	initGL(); //funcion de inicializacion de OpenGL
	
	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);
	
	glutMainLoop(); //bucle de rendering
	//no escribir nada abajo de mainloop
	return 0;
}
