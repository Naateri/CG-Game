#include "Enemy.h"

Enemy1::Enemy1(Player* p){
	location = new Point2D(100.0f, 100.0f);
	srand(time(NULL));
	this->drop_item = rand() % 6;
	this->shoot_idle_time = 1.0f;
	this->move_idle_time = 1.5f;
	this->player = p;
}

void Enemy1::shoot(){
	Bullet* bala = new Bullet(location->x,location->y);
	bullets.push_back(bala);
}

void Enemy1::draw_bullets(){
	Bullet* bl;
	bool hit_enemy;
	for(int i=0;i<bullets.size();++i){
		hit_enemy = false;
		glPushMatrix();
			bullets[i]->location->y -= 3;
			glPointSize(8);
			glBegin(GL_POINTS);
			glColor3d(255, 0, 0);
			glVertex3f(bullets[i]->location->x,bullets[i]->location->y,0);
		glEnd();
		
		if (!hit_enemy && 
			bullets[i]->location->distance(player->location) <= PLAYER_COLLISION){
			player->reduce_hp();
			std::cout << "HP reduced\n";
			hit_enemy = true;
		}
		
		if (hit_enemy || bullets[i]->location->y <= -300.0f){
			bl = bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;
			delete bl;
		}
		
	}
}

void Enemy1::draw(){
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
		glPushMatrix();
			glColor3d(255, 0, 0);
			glTranslatef(location->x, location->y, 0.0f);
			glutSolidTeapot(5);
		glPopMatrix();
	}
	draw_bullets();
}

void Enemy1::move(){
	if (move_left){
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
	}
	
}

float Enemy1::get_hp(){
	return hp;
}

void Enemy1::decrement_hp(){
	hp -= ENEMY_1_DECREMENT;
}

float Enemy1::iscore(){
	return ENEMY_1_SCORE;
}
