#ifndef ENEMY1_H
#define ENEMY1_H
#include <GL/glut.h>
#include <iostream>
#include <vector>

#include "Enemy.h"
#include "Bullet.h"

#define ENEMY_1_SPEED 1.0f

class Enemy1: public Enemy{
private:
	void draw_bullets();
	float speed = ENEMY_1_SPEED;
public:
	Enemy1();
	void shoot();
	void draw();
	void move();
};

class Enemy2: public Enemy{
	
public:
	void shoot();
	void draw();
};

class Enemy3: public Enemy{
	
public:
	void shoot();
	void draw();
};

#endif ENEMY1_H
