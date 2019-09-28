#include "Player.h"

std::vector<Enemy*> enemies;

Player::Player(PS3Controller* PS3){
	this->Joystick = PS3;
	location = new Point2D(0.0f, 0.0f);
	this->hp = 100.0f;
}

void Player::move(){
	int val, num;
	//std::cout << "Waiting for read\n";
	bool end = false;
	do{
		Joystick->read_fd();
		val = Joystick->value; num = Joystick->number;
		if (val > 0 && num == 14){
			this->location->y -= DIFFERENCE;
		} else if (val >0 && num == 13){
			this->location->y += DIFFERENCE;
		} else if (val >0 && num == 16){
			this->location->x += DIFFERENCE;
		} else if (val >0 && num == 15){
			this->location->x -= DIFFERENCE;
		} else if (val > 0 && num == 0){
		//std::cout << "PEW PEW\n";
			shoot();
		} else if (val == 1 && num == 1){
			delete Joystick;
			end = true;
			exit(0);
		}
	} while (!end);
}

void Player::shoot(){
	Bullet* bala = new Bullet(location->x+17,location->y);
	bullets.push_back(bala);
}

void Player::draw_bullets(){
	Bullet* bl;
	for(int i=0;i<bullets.size();++i){
		bullets[i]->location->y += 5;
		bullets[i]->rotation += 15.0f;
		//glPointSize(10);
		//glBegin(GL_POINTS);
		glPushMatrix();
			glColor3d(0,255,0);
			//glVertex3f(bullets[i]->x,bullets[i]->y,0);
			glTranslatef(bullets[i]->location->x, bullets[i]->location->y, 0.0f);
			glRotatef(bullets[i]->rotation, 0.0f, 0.0f, 1.0f);
			glutSolidTeapot(4);
		glPopMatrix();
		//glEnd();
		
		//Collisions//
		
		for(int j = 0; j < enemies.size(); j++){
			Enemy* temp = enemies[j];
			if (temp->location->distance(bullets[i]->location) <= COLLISION){
				enemies.erase(enemies.begin() + j);
				j--;
				delete temp;
				bl = bullets[i];
				bullets.erase(bullets.begin() + i);
				i--;
				delete bl;
				continue;
			}
		}
		
		if (bullets[i]->location->y >= 300){
			bl = bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;
			delete bl;
		}
	}
	//std::cout << "Size: " << bullets.size() << std::endl;
}

void Player::draw(){
	glPushMatrix();
		glColor3d(255, 0, 255);
		glTranslatef(location->x, location->y, 0.0f);
		glutSolidTeapot(10);
	glPopMatrix();
	draw_bullets();
}
