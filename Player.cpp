#include "Player.h"

std::vector<Enemy*> enemies;
std::vector<Item *> items;

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
		//std::cout<<val<<" "<<num<<"\n";
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
		}else if(val>0 && num == 5){
			this->destroyAllEnemiesAndReset();
		} else if (val == 1 && num == 1){
			delete Joystick;
			end = true;
			exit(0);
		}
		
		
	} while (!end);
}

void Player::destroyAllEnemiesAndReset(){
	if(this->hasBomb){
		std::cout<<"Boom\n";
		this->power = 0;
		enemies.clear();
		items.clear();
		bullets.clear();
	}
}

void Player::shoot(){
	if(this->power == 0){
		Bullet* bala = new Bullet(location->x+17,location->y);
		bullets.push_back(bala);
	}else if(this->power == 1){
		Bullet* bala1 = new Bullet(location->x+13,location->y);
		Bullet* bala2 = new Bullet(location->x+22,location->y);
		bullets.push_back(bala1);
		bullets.push_back(bala2);
	}else if(this->power == 2){
		Bullet* bala1 = new Bullet(location->x+17,location->y+10);
		Bullet* bala2 = new Bullet(location->x+17,location->y);
		bullets.push_back(bala1);
		bullets.push_back(bala2);
	}else if(this->power == 3){
		Bullet* bala1 = new Bullet(location->x+13,location->y+10);
		Bullet* bala2 = new Bullet(location->x+22,location->y+10);
		bullets.push_back(bala1);
		bullets.push_back(bala2);
		bala1 = new Bullet(location->x+13,location->y);
		bala2 = new Bullet(location->x+22,location->y);
		bullets.push_back(bala1);
		bullets.push_back(bala2);
	}
}

void Player::draw_bullets(){
	Bullet* bl;
	Enemy* temp;
	for(int i=0;i<bullets.size();++i){
		bool deleted_bullet = false;
		bullets[i]->location->y += 5;
		bullets[i]->rotation += 15.0f;
		//glPointSize(10);
		//glBegin(GL_POINTS);
		if(this->power == 3){
			this->collision = 5.0f;
			glPushMatrix();
				glColor3d(0,255,0);
				//glVertex3f(bullets[i]->x,bullets[i]->y,0);
				glTranslatef(bullets[i]->location->x, bullets[i]->location->y, 0.0f);
				glRotatef(bullets[i]->rotation, 0.0f, 0.0f, 1.0f);
				glutSolidTeapot(2);
			glPopMatrix();
		}else{
			this->collision = 10.0f;
			glPushMatrix();
				glColor3d(0,255,0);
				//glVertex3f(bullets[i]->x,bullets[i]->y,0);
				glTranslatef(bullets[i]->location->x, bullets[i]->location->y, 0.0f);
				glRotatef(bullets[i]->rotation, 0.0f, 0.0f, 1.0f);
				glutSolidTeapot(4);
			glPopMatrix();
		}
		
		//glEnd();
		
		//Collisions//
		
		int enemies_size = enemies.size();
		for(int j = 0; j < enemies_size; j++){
			temp = enemies.at(j);
			if (!deleted_bullet && temp->alive && temp->location->distance(bullets[i]->location) <= this->collision){
				temp->alive = false;
				bl = bullets[i];
				bullets.erase(bullets.begin() + i);
				i--;
				delete bl;
				deleted_bullet = true;
				//continue;
				
				//dropear un Item
				switch(temp->drop_item)
				{
				case 1:
				{
					std::cout << "Drop Item 1" << std::endl;
					DoubleShotItem *power = new DoubleShotItem(temp->location->x,temp->location->y);
					items.push_back(power);
				}
					break;
				case 2:{
					std::cout << "Drop Item 2" << std::endl;
					DoubleBulletItem *power = new DoubleBulletItem(temp->location->x,temp->location->y);
					items.push_back(power);
				}
					break;
				case 3:{
					std::cout << "Drop Item 3" << std::endl;
					DoubleShotBulletItem *power = new DoubleShotBulletItem(temp->location->x,temp->location->y);
					items.push_back(power);
				}
					break;
				case 4:
					std::cout << "Drop Item 4" << std::endl;
					break;
				case 5:{
					std::cout << "Drop Item 5" << std::endl;
					if(!this->hasBomb){
						SuperBombItem *power = new SuperBombItem(temp->location->x,temp->location->y);
						items.push_back(power);
					}
					
				}
					break;
				default:
					std::cout << "Drop Nothing" << std::endl;
				}
				
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
	//std::cout << "Size: " << bullets.size() << std::endl;
}

void Player::checkItemCollision(){
	for(int i = 0;i<items.size();i++){
		//std::cout<<"distancia item "<<i<<this->location->distance(items[i]->location)<<std::endl;
		if(items[i]->location->y<-140){
			items[i]->active = false;
		}else if(this->location->distance(items[i]->location)<=COLLISION){
			items[i]->active = false;
			if(items[i]->id == 5){
				this->hasBomb = true;
				
			}else{
				this->power = items[i]->id;
			}
			
		}
	}
	Item *temp;
	for(int i = 0;i<items.size();i++){
		temp = items[i];
		if(!temp->active){
			items.erase(items.begin()+i);
			i--;
			delete temp;
			std::cout<<items.size()<<std::endl;
		}
	}
}

void Player::draw(){
	this->checkItemCollision();
	glPushMatrix();
		glColor3d(255, 0, 255);
		glTranslatef(location->x, location->y, 0.0f);
		glutSolidTeapot(10);
	glPopMatrix();
	draw_bullets();
}
