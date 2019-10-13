#ifndef Player_H
#define Player_H

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <chrono>
#include "Controller.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Point.h"

#define DIFFERENCE 20
#define COLLISION 10.0f

class Enemy;

class Player{
private:
	PS3Controller* Joystick;
	//float x, y;
	int hp;
	std::chrono::steady_clock::time_point begin; //time measurement
	std::chrono::steady_clock::time_point end; //so game ends in 2 minutes
	std::vector<Bullet*> bullets;
	void draw_bullets();
public:
	Point2D* location;
	Player(PS3Controller*);
	void add_hp();
	void reduce_hp();
	void kill_player(){ this->hp = 0; };
	void move();
	void shoot();
	void draw();
	double time_passed();
	bool is_alive();
};

extern std::vector<Enemy*> enemies;

#endif
