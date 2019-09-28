#ifndef ENEMY1_H
#define ENEMY1_H
#include <GL/glut.h>
#include <iostream>
#include <vector>

#include "Enemy.h"
#include "Bullet.h"

class Enemy1: public Enemy{
private:
	void draw_bullets();
	std::vector<Bullet*> bullets;
public:
	Enemy1();
	void shoot();
	void draw();
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
