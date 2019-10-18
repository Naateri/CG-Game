#include "Enemy.h"

Enemy3::Enemy3(Player *cplayer) {
	location = new Point2D(100.0f, 100.0f);
	this->shoot_idle_time = 1.0f;
	this->move_idle_time = 1.5f;
	this->cplayer = cplayer;
	this->rotate = false;
}

void Enemy3::shoot(){
	Bullet* bala = new Bullet(location->x,location->y);
	bullets.push_back(bala);
}

void Enemy3::draw_bullets(){
	Bullet* bl;
	bool hit_enemy;
	for(int i=0;i<bullets.size();++i){
		hit_enemy = false;
		if(bullets[i]->location->y >=  TOP ){
			if(bullets[i]->location->x > cplayer->getX()){
				bullets[i]->location->x -= 1;
			}
			else{
				bullets[i]->location->x +=1;
			}
		}
		
		bullets[i]->location->y -= 2;
		glPushMatrix();
		glPointSize(8);
		glBegin(GL_POINTS);
		glColor3d(255, 255, 0);
		glVertex3f(bullets[i]->location->x,bullets[i]->location->y,0);
		glEnd();
		
		if (!hit_enemy && 
			bullets[i]->location->distance(cplayer->location) <= PLAYER_COLLISION){
			cplayer->reduce_hp();
			std::cout << "HP reduced\n";
			hit_enemy = true;
		}
		
		if (hit_enemy || bullets[i]->location->y <= -300.0f){
			bl = bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;
			delete bl;
		}
		
		glPopMatrix();
	}
}

void Enemy3::draw(){
	if (alive){
		if (!shot){
			this->begin = std::chrono::steady_clock::now();
			shot = true;
		} else {
			this->end = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = this->end - this->begin;
			double time = elapsed_seconds.count();
			
			if (time >= shoot_idle_time){
				this->shot = false;
				shoot();
			}
			//std::cout << "time: " << time << std::endl;
		}
		if(!rotate){
			glPushMatrix();
			glColor3d(255, 255, 240);
			glTranslatef(location->x, location->y, 0.0f);
			glutSolidTeapot(5);
			glPopMatrix();
		}else{
			this->location->x = (cplayer->location->x+4) * cos(this->rotation+=this->rotationSpeed);
			this->location->y = (cplayer->location->y+4) * sin(this->rotation+=this->rotationSpeed);
			glPushMatrix();
			glColor3d(255, 255, 240);
			glTranslatef(location->x, location->y, 0.0f);
			glutSolidTeapot(5);
			glPopMatrix();
		}
		
	}
	draw_bullets();
}

void Enemy3::move(){
	/*if (move_left){
		if (location->x <= -120.0f){
			move_left = false;
			move_right = true;
			location->y -= 20.0f;
		} else {
			location->x -= this->speed;
		}
	} else if (move_right){
		if (location->x >= 120.0f){
			move_left = true;
			move_right = false;
			location->y -= 20.0f;
		} else {
			location->x += this->speed;
		}
	}*/
	if(location->distance(cplayer->location) >= 30.0 ){
		//if(location->x > cplayer->getX()){
			location->y -= 2;
			location->x -= 1;
		//}
	}else{
		rotate = true;
		
		
	}
	
	
}

float Enemy3::get_hp(){
	return hp;
}

void Enemy3::decrement_hp(){
	hp -= ENEMY_3_DECREMENT;
}

float Enemy3::iscore(){
	return ENEMY_3_SCORE;
}
