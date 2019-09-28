#ifndef BULLET_H
#define BULLET_H

class Bullet{
public:
	float damage;
	float x;
	float y;
	
	Bullet(){
		this->damage = 0;
		this->x = 0;
		this->y = 0;
	}
	
	Bullet(float px, float py){
		//this->damage = 0;
		this->x = px;
		this->y = py;
	}
};

//extern std::vector<Bullet*> bullets;

#endif
