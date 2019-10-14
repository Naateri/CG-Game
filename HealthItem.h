#ifndef HEALTHITEM_H
#define HEALTHITEM_H
#include "Item.h"
#define HEALTHITEM_SPEED 1.5f

class HealthItem :public Item{
public:
	HealthItem(int x, int y);
	void draw();
	void move();
private:
};

#endif

