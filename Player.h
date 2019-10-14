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
#include "DoubleShotItem.h"
#include "DoubleBulletItem.h"
#include "DoubleShotBulletItem.h"
#include "SuperBombItem.h"

#define HEIGHT 120
#define DIFFERENCE 20
#define COLLISION 10.0f

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
};

extern std::vector<Enemy*> enemies;
extern std::vector<Item*> items;

#endif
