#include "Enemy.h"

Enemy2::Enemy2(Player *cplayer,GLint texture) {
	srand(time(NULL));
	this->drop_item = rand() % 6;
	location = new Point2D(100.0f, 100.0f);
	this->shoot_idle_time = 1.0f;
	this->move_idle_time = 1.5f;
	this->cplayer = cplayer;
	this->texture2 = texture;
}

void Enemy2::shoot(){
	Bullet* bala = new Bullet(location->x,location->y);
	bullets.push_back(bala);
}

void Enemy2::draw_bullets(){
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

void Enemy2::drawEnemy(){
	float h = 9;
	float w = 10;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glBegin(GL_QUADS);
	glColor3f(1.0,1.0,1.0);
	glTexCoord2f(1,0);//coordenadas de textura
	glVertex3d(-w, -h, 0);
	
	glTexCoord2f(1,1);
	glVertex3d(-w, h, 0);
	
	glTexCoord2f(0,1);
	glVertex3d(w, h, 0);
	
	glTexCoord2f(0,0);
	glVertex3d(w, -h, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Enemy2::draw(){
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
		glColor3d(255, 255, 0);
		glTranslatef(location->x, location->y, 0.0f);
		drawEnemy();
		//glutSolidTeapot(5);
		glPopMatrix();
	}
	draw_bullets();
}

void Enemy2::move(){
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

float Enemy2::get_hp(){
	return hp;
}

void Enemy2::decrement_hp(){
	hp -= ENEMY_2_DECREMENT;
}

float Enemy2::iscore(){
	return ENEMY_2_SCORE;
}
