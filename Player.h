#ifndef Player_H
#define Player_H

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Controller.h"
#include "Bullet.h"

#define DIFFERENCE 20

class Player{
private:
	PS3Controller* Joystick;
	float x, y, z;
	float hp;
	std::vector<Bullet*> bullets;
	void draw_bullets();
public:
	Player(PS3Controller*);
	void move();
	void shoot();
	void draw();
};

#endif
