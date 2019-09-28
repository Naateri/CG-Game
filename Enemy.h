#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <chrono>

class Enemy{
protected:
	float hp;
	float x,y;
	bool shot = false;
	float shoot_idle_time;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
public:
	virtual void shoot() = 0;
	virtual void draw() = 0;
};

#endif
