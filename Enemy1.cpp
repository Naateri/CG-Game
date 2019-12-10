#include "Enemy.h"

//GLint enemy_bullets;

Enemy1::Enemy1(Player* p,GLint texture){
	location = new Point2D(100.0f, 100.0f);
	srand(time(NULL));
	this->drop_item = rand() % 6;
	this->shoot_idle_time = 1.0f;
	this->move_idle_time = 1.5f;
	this->player = p;
	this->texture1 = texture;
}

void Enemy1::shoot(){
	Bullet* bala = new Bullet(location->x,location->y);
	bullets.push_back(bala);
}

void Enemy1::draw_bullets(){
	Bullet* bl;
	bool hit_enemy;
	rotation += 8.0f;
	for(int i=0;i<bullets.size();++i){
		hit_enemy = false;
		glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			bullets[i]->location->y -= 3;
			
			glTranslatef(bullets[i]->location->x,bullets[i]->location->y,0);
			glRotatef(rotation,0,1,0);
			glTranslatef(0.0f,0.0f,0.0f);
			glRotatef(90,1,0,0);

			GLUquadricObj *quadratic = gluNewQuadric();
			gluQuadricDrawStyle(quadratic, GLU_FILL);
			glBindTexture(GL_TEXTURE_2D, enemy_bullets);

			gluQuadricTexture(quadratic, GL_TRUE);
			gluCylinder(quadratic,1.5f,1.5f,8,32,32);

			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
			glDisable(GL_TEXTURE_2D);
			
		glPopMatrix();
		
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

void Enemy1::drawEnemy(){
	float h = 9;
	float w = 10;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture1);
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
			glTranslatef(location->x, location->y, 0.0f);
			drawEnemy();
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
