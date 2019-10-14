#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#include "Point.h"
#include "Bullet.h"

class Enemy{
protected:
	float hp;
	bool shot = false;
	bool moved = false;
	bool move_right = false;
	bool move_left = true;
	bool move_down = false;
	float shoot_idle_time;
	float move_idle_time;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	
	std::chrono::steady_clock::time_point begin_m; //movement
	std::chrono::steady_clock::time_point end_m;
	
	virtual void draw_bullets() = 0;
	
public:
	std::vector<Bullet*> bullets;
	Point2D* location;
	int drop_item;
	bool alive = true;
	virtual void shoot() = 0;
	virtual void draw() = 0;
	virtual void move() = 0;
};

#endif
