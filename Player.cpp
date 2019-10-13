#include "Player.h"

std::vector<Enemy*> enemies;

Player::Player(PS3Controller* PS3){
	this->Joystick = PS3;
	location = new Point2D(0.0f, 0.0f);
	this->hp = 5; //health points
	this->begin = std::chrono::steady_clock::now();
}

void Player::add_hp(){
	this->hp++;
}

void Player::reduce_hp(){
	this->hp--;
}



void Player::move(){
	int val, num;
	
	bool end = false;
	do{
		Joystick->read_fd();
		val = Joystick->value; num = Joystick->number;
		if (val > 0 && num == 14){//arriba
			this->location->y -= DIFFERENCE;
			if(location->y < BOTTOM){/// detectar limites de la ventana
				this->location->y += DIFFERENCE;
			}
		} else if (val >0 && num == 13){//abajo
			this->location->y += DIFFERENCE;
			if(location->y > TOP){/// detectar limites de la ventana
				this->location->y -= DIFFERENCE;
			}
		} else if (val >0 && num == 16){
			this->location->x += DIFFERENCE;
			if(location->x > HEIGHT){/// detectar limites de la ventana
				this->location->x -= DIFFERENCE;
			}
		} else if (val >0 && num == 15){
			this->location->x -= DIFFERENCE;
			if(location->x < -HEIGHT){/// detectar limites de la ventana
				this->location->x += DIFFERENCE;
			}
		}else if (val > 0 && num == 0){
			shoot();
		} else if (val == 1 && num == 1){
			delete Joystick;
			end = true;
			exit(0);
		}
		
	//	std::cout<< location->x <<" - " <<location->y <<std::endl;
		
	} while (!end);
}

void Player::shoot(){
	Bullet* bala = new Bullet(location->x+17,location->y); /// para que salga de la tetera
	bullets.push_back(bala);
}

void Player::draw_bullets(){
	Bullet* bl;
	Enemy* temp;
	for(int i=0;i<bullets.size();++i){
		bool deleted_bullet = false;
		bullets[i]->location->y += 5;
		bullets[i]->rotation += 15.0f;
		
		glPushMatrix();
		glColor3d(0,255,0);
		glTranslatef(bullets[i]->location->x, bullets[i]->location->y, 0.0f);
		glRotatef(bullets[i]->rotation, 0.0f, 0.0f, 1.0f);
		glutSolidTeapot(4);
		glPopMatrix();
		
		
		//Collisions//
		
		int enemies_size = enemies.size();
		
		for(int j = 0; j < enemies_size; j++){
			temp = enemies.at(j);
			if (!deleted_bullet && temp->alive && temp->location->distance(bullets[i]->location) <= COLLISION){
				temp->alive = false;
				bl = bullets[i];
				bullets.erase(bullets.begin() + i);
				i--;
				delete bl;
				deleted_bullet = true;
			}
			
			if (!temp->alive && temp->bullets.size() <= 0){
				enemies.erase(enemies.begin() + j);
				j--;
				enemies_size--;
				delete temp;
			}
		}
		
		if (!deleted_bullet){
			if (bullets[i]->location->y >= 300){
				bl = bullets[i];
				bullets.erase(bullets.begin() + i);
				i--;
				delete bl;				
			}
		}
	}
	
}

void Player::draw(){
	glPushMatrix();
	glColor3d(255, 0, 255);
	glTranslatef(location->x, location->y, 0.0f);
	glutSolidTeapot(10);
	glPopMatrix();
	draw_bullets();
}

double Player::time_passed(){
	this->end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds = this->end - this->begin;
	double time = elapsed_seconds.count();
	return time;
}

bool Player::is_alive(){
	return (this->hp > 0);
}

float Player::getX(){
	return location->x;
}
