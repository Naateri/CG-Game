#include "Player.h"

Player::Player(PS3Controller* PS3){
	this->Joystick = PS3;
	this->x = 0.0f; this->y = 0.0f;
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
		this->y -= DIFFERENCE;
	} else if (val >0 && num == 13){
		this->y += DIFFERENCE;
	} else if (val >0 && num == 16){
		this->x += DIFFERENCE;
	} else if (val >0 && num == 15){
		this->x -= DIFFERENCE;
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
	Bullet* bala = new Bullet(x+17,y);
	bullets.push_back(bala);
}

void Player::draw_bullets(){
	Bullet* bl;
	for(int i=0;i<bullets.size();++i){
		bullets[i]->y += 5;
		glPointSize(10);
		glBegin(GL_POINTS);
		glVertex3f(bullets[i]->x,bullets[i]->y,0);
		glEnd();
		if (bullets[i]->y >= 300){
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
		glTranslatef(x, y, 0.0f);
		glutSolidTeapot(10);
	glPopMatrix();
	draw_bullets();
}
