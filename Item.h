#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <chrono>
#include "Point.h"

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

#endif

