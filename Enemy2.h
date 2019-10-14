#ifndef ENEMY2_H
#define ENEMY2_H

#include <GL/glut.h>
#include <iostream>
#include <vector>

#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"

#define ENEMY_2_SPEED 1.0f

class Enemy2: public Enemy{
private:
	void draw_bullets();
	float speed = ENEMY_2_SPEED;
	Player* cplayer;
public:
	Enemy2(Player* cplayer);
	void shoot();
	void draw();
	void move();
};






#endif 

