#include "Item.h"

DoubleShotItem::DoubleShotItem(int x, int y) {
	this->id = 1;
	this->location =  new Point2D(x,y);
}


void DoubleShotItem::draw(){
	if(this->active){
		//std::cout<<location->y<<std::endl;
		glPushMatrix();
			glColor3d(255, 255, 0);
			glTranslatef(location->x, location->y, 0.0f);
			glutSolidCube(5);
		glPopMatrix();
	}
}

void DoubleShotItem::move(){
	if(this->active){
		location->y -= DOUBLE_SHOT_ITEM_SPEED;
	}
	
}

