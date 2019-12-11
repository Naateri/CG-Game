#include "Enemy.h"

Enemy3::Enemy3(Player *cplayer,GLint texture) {
	location = new Point2D(100.0f, 100.0f);
	this->shoot_idle_time = 1.0f;
	this->move_idle_time = 1.5f;
	this->cplayer = cplayer;
	this->rotate = false;
	this->texture3 = texture; 
}

void Enemy3::shoot(){
	Bullet* bala = new Bullet(location->x,location->y);
	bala->m = ((this->location->y - cplayer->getY())/(this->location->x - cplayer->getX()));
	bala->n = cplayer->getY();
	bala->xPlayer = cplayer->getX();
	if(this->location->x == 0 && this->location->y>=0){
		bala->direction = 1;
	}else if(this->location->x == 0 && this->location->y<0){
		bala->direction = 0;
	}else if(this->location->x>0){
		bala->direction = 1;
	}else{
		bala->direction = 0;
	}
	bullets.push_back(bala);
}

void Enemy3::draw_bullets(){
	Bullet* bl;
	bool hit_enemy;
	for(int i=0;i<bullets.size();++i){
		hit_enemy = false;
		/*glPushMatrix();
		
			glRotatef(90,1,0,0);
			
			GLUquadricObj *quadratic = gluNewQuadric();
			glTranslatef(bullets[i]->location->x,bullets[i]->location->y,0);
			gluQuadricDrawStyle(quadratic, GLU_FILL);
			glBindTexture(GL_TEXTURE_2D, enemy_bullets);
			gluQuadricTexture(quadratic, GL_TRUE);
			gluQuadricNormals(quadratic, GLU_SMOOTH);
			gluCylinder(quadratic,1.8f,1.8f,4,32,32);
		glPopMatrix();
		
		*/
		
		
		glPushMatrix();
		//bullets[i]->location->y -= 2;
		
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			
			
			glTranslatef(bullets[i]->location->x,bullets[i]->location->y,0);
			glRotatef(rotation,0,1,0);
			glTranslatef(0.0f,0.0f,0.0f);
			glRotatef(90,1,0,0);
			
			GLUquadricObj *quadratic = gluNewQuadric();
			gluQuadricDrawStyle(quadratic, GLU_FILL);
			glBindTexture(GL_TEXTURE_2D, enemy_bullets2);
			
			gluQuadricTexture(quadratic, GL_TRUE);
			gluQuadricNormals(quadratic, GLU_SMOOTH);
			gluCylinder(quadratic,1.5f,1.5f,8.0f,32,32);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
			glDisable(GL_TEXTURE_2D);
		
		glPopMatrix();
		
		
		
		
		
		
		
		
	
		bullets[i]->location->y = (bullets[i]->m * (bullets[i]->location->x-bullets[i]->xPlayer)) + bullets[i]->n;
		
		if(bullets[i]->direction){
			bullets[i]->location->x -= 0.5;
		}
		else{
			bullets[i]->location->x += 0.5;
		}
		

		if (!hit_enemy && bullets[i]->location->distance(cplayer->location) <= PLAYER_COLLISION){
			std::cout << "HP reduced\n";
			cplayer->reduce_hp();
			hit_enemy = true;
		}
		
		if (hit_enemy || bullets[i]->location->y <= -300.0f || bullets[i]->location->y >= 300.0f|| bullets[i]->location->x >= 300.0f || bullets[i]->location->x <= -300.0f){
			bl = bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;
			delete bl;
		}
		
		glPopMatrix();
	}
}

void Enemy3::drawEnemy(){
	float h = 9;
	float w = 10;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture3);
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

void Enemy3::draw(){
	if (alive){
		if (!shot){
			this->begin = std::chrono::steady_clock::now();
			shot = true;
		} 
		else {
			this->end = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = this->end - this->begin;
			double time = elapsed_seconds.count();
			
			if (time >= shoot_idle_time){
				this->shot = false;
				shoot();
			}
			
		}
		if(!rotate){
			glPushMatrix();
				glTranslatef(location->x, location->y, 0.0f);
				drawEnemy();
			glPopMatrix();
		}
		else{
			this->location->x = 55 * cos(this->rotation+=this->rotationSpeed) + cplayer->location->x;
			this->location->y = 55 * sin(this->rotation+=this->rotationSpeed) + cplayer->location->y;
		

			
			
			
			glPushMatrix();
				glTranslatef(location->x, location->y, 0.0f);
				drawEnemy();
			glPopMatrix();
		}
		
	}
	draw_bullets();
}

void Enemy3::move(){
	if(location->distance(cplayer->location) >= 55 ){
		if(this->location->x > cplayer->getX()){
			this->location->x -= 1;
		}
		else{
			this->location->x +=1;
		}
		
		this->location->y -= 1;
		//location->y = ((location->x - cplayer->getX())/(location->y-cplayer->getY())) * (-cplayer->getX()+location->x)+cplayer->getY();
		//location->x -= 1.5;
	}
	else{
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
