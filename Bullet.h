
#ifndef BULLET_H
#define BULLET_H

#include "Point.h"

class Bullet{
public:
	float damage;
	Point2D* location;
	float rotation = 0.0f;
	GLfloat m;
	GLfloat n;
	bool direction;
	
	Bullet(){
		location = new Point2D(0,0);
		this->damage = 0;
		this->location->x = 0;
		this->location->y = 0;
	}
		
	Bullet(float px, float py){
		//this->damage = 0;
		location = new Point2D(px, py);
	}
};

//extern std::vector<Bullet*> bullets;

#endif
