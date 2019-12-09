#ifndef Player_H
#define Player_H

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <chrono>
#include "Controller.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Item.h"
#include "Point.h"
#include "TextureManager.h"
#define HEIGHT 120
#define DIFFERENCE 2
#define COLLISION 10.0f
using namespace std ;
class Enemy;

class Player{
private:
	int power;
	PS3Controller* Joystick;
	
	//float x, y;
	float collision = 10.0f;
	int hp;
	std::chrono::steady_clock::time_point begin; //time measurement
	std::chrono::steady_clock::time_point end; //so game ends in 2 minutes
	
	std::vector<Bullet*> bullets;
	
	void draw_bullets();
	void checkItemCollision();
	
public:
	bool hasBomb = false;
	Point2D* location;
	Player(PS3Controller*);
	void add_hp();
	void reduce_hp();
	void kill_player(){ this->hp = 0; };
	void move();
	void shoot();
	void draw();
	void destroyAllEnemiesAndReset();
	double time_passed();
	bool is_alive();
	float getX();
	float getY();
	int score = 0;
	
	///Texturas
	void draw_health(int i);
	void itemTextures();
	void draw_player();
	void loadTexture();
	int time1 = 0;
	int timebase = 0;
	int anim = 0;
	int i=0;
	GLint salud[9];

	GLint texture_player;
	
};

extern std::vector<Enemy*> enemies;
extern std::vector<Item*> items;

#endif
