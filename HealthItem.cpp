#include "HealthItem.h"

HealthItem::HealthItem(int x, int y) {
	this->id = 4;
	this->location = new Point2D(x,y);
}

void HealthItem::draw(){
	if(this->active){
		//std::cout<<location->y<<std::endl;
		glPushMatrix();
		glColor3d(255, 255, 255);
		glTranslatef(location->x, location->y, 0.0f);
		glutSolidCube(5);
		glPopMatrix();
	}
}

void HealthItem::move(){
	if(this->active){
		location->y -= HEALTHITEM_SPEED;
	}
}
