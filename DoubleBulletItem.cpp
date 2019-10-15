#include "Item.h"

DoubleBulletItem::DoubleBulletItem(int x, int y) {
	this->id = 2;
	this->location =  new Point2D(x,y);
}

void DoubleBulletItem::draw(){
	if(this->active){
		//std::cout<<location->y<<std::endl;
		glPushMatrix();
		glColor3d(0, 255, 0);
		glTranslatef(location->x, location->y, 0.0f);
		glutSolidCube(5);
		glPopMatrix();
	}
}

void DoubleBulletItem::move(){
	if(this->active){
		location->y -= DOUBLE_BULLET_ITEM_SPEED;
	}
	
}
