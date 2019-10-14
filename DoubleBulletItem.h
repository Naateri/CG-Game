#ifndef DOUBLEBULLETITEM_H
#define DOUBLEBULLETITEM_H
#include "Item.h"
#define DOUBLEBULLET_ITEM_SPEED 1.5f 

class DoubleBulletItem : public Item {
public:
	DoubleBulletItem(int x, int y);
	void draw();
	void move();

};

#endif

