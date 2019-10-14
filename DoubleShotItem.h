#ifndef DOUBLESHOTITEM_H
#define DOUBLESHOTITEM_H
#include "Item.h"
#define DOUBLESHOT_ITEM_SPEED 0.5f 

class DoubleShotItem: public Item {
public:
	DoubleShotItem(int x, int y);
	//void powerUp(Player *p);
	void draw();
	void move();
private:
};

#endif

