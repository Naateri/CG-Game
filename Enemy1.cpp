#include "Enemy1.h"

Enemy1::Enemy1(){
	this->x = 0.0f;
	this->y = 100.0f;
	this->shoot_idle_time = 1.0f;
}

void Enemy1::shoot(){
	Bullet* bala = new Bullet(x,y);
	bullets.push_back(bala);
}

void Enemy1::draw_bullets(){
	Bullet* bl;
	for(int i=0;i<bullets.size();++i){
		bullets[i]->y -= 3;
		glPointSize(8);
		glBegin(GL_POINTS);
		glColor3d(255, 0, 0);
		glVertex3f(bullets[i]->x,bullets[i]->y,0);
		glEnd();
	}
}

void Enemy1::draw(){
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
		std::cout << "time: " << time << std::endl;
	}
	glPushMatrix();
		glColor3d(255, 0, 0);
		glTranslatef(x, y, 0.0f);
		glutSolidTeapot(5);
	glPopMatrix();
	draw_bullets();
}
