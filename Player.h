#ifndef Player_H
#define Player_H

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Controller.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Point.h"

#define WIDTH 120
#define HEIGHT 120
#define DIFFERENCE 20
#define COLLISION 10.0f

class Player{
private:
	PS3Controller* Joystick;
	//float x, y;
	Point2D* location;
	float hp;
	std::vector<Bullet*> bullets;
	void draw_bullets();
public:
	Player(PS3Controller*);
	void move();
	void shoot();
	void draw();
};

extern std::vector<Enemy*> enemies;

#endif
