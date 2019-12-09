#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <chrono>
#include "Point.h"
#include <vector>
#define DOUBLE_SHOT_BULLET_ITEM_SPEED 2.5f
#include "TextureManager.h"
#define DOUBLE_BULLET_ITEM_SPEED 1.5f 
#define DOUBLE_SHOT_ITEM_SPEED 0.5f 
#define SUPER_BOMB_SPEED 3.0f
#define HEALTH_ITEM_SPEED 1.5f
using namespace std;
/**
Id 1 disparo doble Color amarillo
Id 2 doble bala Color Verde
Id 3 combiancion del 1 y 2 Color Azul
Id 4 vidas max 3 vidas
Id 5 bomba


**/
class Item {
protected:
	
	float duration_time;
	//virtual void powerUp(Player *p) = 0;
	
public:
	int id;
	Point2D *location;
	bool active = true;
	virtual void draw() = 0;
	virtual void move() = 0;
	
};

class DoubleShotBulletItem : public Item{
public:
	DoubleShotBulletItem(int x, int y);
	void draw();
	void move();
	///Texturas
	void draw_item(int i);
	
	int time1 = 0;
	int timebase = 0;
	int anim = 0;
	int i=0;
	
	
	
private:
};



class DoubleBulletItem : public Item {
public:
	DoubleBulletItem(int x, int y );
	void draw_item(int i);
	void draw();
	void move();
	int time1 = 0;
	int timebase = 0;
	int anim = 0;
	int i=0;

};



class DoubleShotItem : public Item {
public:
	DoubleShotItem(int x, int y);
	//void powerUp(Player *p);
	void draw_item(int i);
	void draw();
	void move();
	int time1 = 0;
	int timebase = 0;
	int anim = 0;
	int i=0;
	
	
private:
};


class SuperBombItem :public Item{
public:
	SuperBombItem(int x, int y);
	void draw();
	void draw_item(int i);
	void move();
	int time1 = 0;
	int timebase = 0;
	int anim = 0;
	int i=0;
	
	
private:
};



class HealthItem :public Item{
public:
	HealthItem(int x, int y);
	void draw_item(int i);
	void draw();
	void move();
	int time1 = 0;
	int timebase = 0;
	int anim = 0;
	int i=0;
	
	
private:
};


extern GLint health1[9];
extern GLint blue[7];
extern GLint red[7];
extern GLint green[7];
extern GLint yellow[7];


#endif

