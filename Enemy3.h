#ifndef ENEMY3_H
#define ENEMY3_H
#include "Enemy.h"
#include "Player.h"

class Enemy3 : public Enemy{
private:
	void draw_bullets();
	float speed = ENEMY_2_SPEED;
	Player* cplayer;
public:
	Enemy3();
	void shoot();
	void draw();
	void move();

};

#endif

