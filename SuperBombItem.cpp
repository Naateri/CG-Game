#include "Item.h"

SuperBombItem::SuperBombItem(int x, int y) {
	this->id = 5;
	this->location = new Point2D(x,y);
}

void SuperBombItem::draw(){
	if(this->active){
		//std::cout<<location->y<<std::endl;
		glPushMatrix();
		glColor3d(0, 255, 255);
		glTranslatef(location->x, location->y, 0.0f);
		glutSolidCube(3);
		glPopMatrix();
	}
}

void SuperBombItem::move(){
	if(this->active){
		location->y -= SUPER_BOMB_SPEED;
	}
}
