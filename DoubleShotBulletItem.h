#ifndef DOUBLESHOTBULLETITEM_H
#define DOUBLESHOTBULLETITEM_H
#include "Item.h"
#define DOUBLEBULLET_ITEM_SPEED 2.5f

class DoubleShotBulletItem : public Item{
public:
	DoubleShotBulletItem(int x, int y);
	void draw();
	void move();
private:
};

#endif

