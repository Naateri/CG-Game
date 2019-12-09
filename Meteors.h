#ifndef METEORS_H
#define METEORS_H

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "Player.h"

#define METEOR_SPEED 1.0f
#define ROTATION_SPEED 2.0f
#define METEOR_PLAYER_COLLISION 10.0f

class Meteor{
private:
	Point2D* move_to;
	Point2D* position;
	Player* p;
	float rotation = 0.0f;
public:
	Meteor(Player*);
	void move();
	void draw();
	bool player_collision();
};

#endif


extern GLint meteor_texture;
