#include "DoubleShotBulletItem.h"

DoubleShotBulletItem::DoubleShotBulletItem(int x, int y) {
	this->id = 3;
	this->location =  new Point2D(x,y);
	
}

void DoubleShotBulletItem::draw(){
	if(this->active){
		//std::cout<<location->y<<std::endl;
		glPushMatrix();
		glColor3d(0, 0, 255);
		glTranslatef(location->x, location->y, 0.0f);
		glutSolidCube(5);
		glPopMatrix();
	}
}

void DoubleShotBulletItem::move(){
	if(this->active){
		location->y -= DOUBLEBULLET_ITEM_SPEED;
	}	
}
