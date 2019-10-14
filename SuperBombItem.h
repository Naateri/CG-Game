#ifndef SUPERBOMBITEM_H
#define SUPERBOMBITEM_H
#include "Item.h"
#define SUPERBOMB_SPEED 3.0f
class SuperBombItem :public Item{
public:
	SuperBombItem(int x, int y);
	void draw();
	void move();
private:
};

#endif

