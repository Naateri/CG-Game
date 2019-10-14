#ifndef Player_H
#define Player_H

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Controller.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Item.h"
#include "Point.h"
#include "DoubleShotItem.h"
#include "DoubleBulletItem.h"
#include "DoubleShotBulletItem.h"
#include "SuperBombItem.h"

#define DIFFERENCE 20
#define COLLISION 10.0f

class Player{
private:
	int power;
	PS3Controller* Joystick;
	//float x, y;
	Point2D* location;
	float hp;
	float collision = 10.0f;
	std::vector<Bullet*> bullets;
	void draw_bullets();
	void checkItemCollision();
public:
	bool hasBomb = false;
	Player(PS3Controller*);
	void move();
	void shoot();
	void draw();
	void destroyAllEnemiesAndReset();
};

extern std::vector<Enemy*> enemies;
extern std::vector<Item*> items;

#endif
