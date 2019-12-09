#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#include "Point.h"
#include "Bullet.h"
#include "Player.h"

#define PLAYER_COLLISION 10.0f
#define ENEMY_1_SPEED 1.0f
#define ENEMY_2_SPEED 1.0f
#define ENEMY_3_SPEED 1.0f

#define ENEMY_1_HP 3.0f
#define ENEMY_2_HP 6.0f
#define ENEMY_3_HP 3.0f

#define ENEMY_1_DECREMENT 1.0f
#define ENEMY_2_DECREMENT 1.0f
#define ENEMY_3_DECREMENT 1.0f

#define ENEMY_1_SCORE 5
#define ENEMY_2_SCORE 10
#define ENEMY_3_SCORE 15

class Player;

class Enemy{
protected:
	bool shot = false;
	bool moved = false;
	bool move_right = false;
	bool move_left = true;
	bool move_down = false;
	bool item;
	float shoot_idle_time;
	float move_idle_time;
	Player* player;
	
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	
	std::chrono::steady_clock::time_point begin_m; //movement
	std::chrono::steady_clock::time_point end_m;
	
	virtual void draw_bullets() = 0;
	
public:
	
	virtual void drawEnemy() = 0;
	std::vector<Bullet*> bullets;
	Point2D* location;
	int drop_item;
	int enemy_live;
	bool alive = true;
	virtual void shoot() = 0;
	virtual void draw() = 0;
	virtual void move() = 0;
	virtual float get_hp() = 0;
	virtual void decrement_hp() = 0;
	virtual float iscore() = 0;
};


class Enemy1: public Enemy{
private:
	void draw_bullets();
	float speed = ENEMY_1_SPEED;
	float hp = ENEMY_1_HP;
	
public:
	GLint texture1;
	
	Enemy1(Player*, GLint texture);
	void drawEnemy();
	void shoot();
	void draw();
	void move();
	float get_hp();
	void decrement_hp();

	float iscore();
};


class Enemy2: public Enemy{
private:
	void draw_bullets();
	float speed = ENEMY_2_SPEED;
	float hp = ENEMY_2_HP;
	Player* cplayer;
public:
	GLint texture2;
	
	Enemy2(Player* cplayer,GLint texture);
	void drawEnemy();
	void shoot();
	void draw();
	void move();
	float get_hp();
	void decrement_hp();
	float iscore();
};


class Enemy3: public Enemy{
	void draw_bullets();
	float speed = ENEMY_3_SPEED;
	float hp = ENEMY_3_HP;
	Player* cplayer;
	GLfloat rotation = 0.0;
	GLfloat rotationSpeed = 5.0;
	bool rotate;
public:
	GLint texture3;
	
	Enemy3(Player *cplayer,GLint texture);
	void drawEnemy();
	void shoot();
	void draw();
	void move();
	float get_hp();
	void decrement_hp();
	float iscore();
};





#endif
