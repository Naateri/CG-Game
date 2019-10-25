#include "Player.h"

std::vector<Enemy*> enemies;
std::vector<Item *> items;

Player::Player(PS3Controller* PS3){
	this->Joystick = PS3;
	this->score = 0;
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
	Joystick->read_fd();
	while (!end){
		
		
		
		
		
		Joystick->init();
		pair<int,int> control = Joystick->controls();
		
		if(Joystick->isButton){
			
			val = Joystick->value; 
			num = control.first;
			cout<<"VALOR"<<val<<"   NUM "<<num<<endl;
			if ( num == 0){
				shoot();
			}else if(val>0 && num == 5){
				this->destroyAllEnemiesAndReset();
			} else if (val == 1 && num == 1){
				delete Joystick;
				end = true;
				exit(0);
			}
			
			
			
			
		}
		else{
		
		
			cout<<"Controles: "<<control.first<<"   "<<control.second<<endl;
		
			this->location->x += control.first * DIFFERENCE;
			this->location->y -= control.second * DIFFERENCE;
			cout<<"X esta en :"<<this->location->x<<endl;
			cout<<"Y esta en :"<<this->location->y<<endl;
			
			
			if(location->y > TOP){/// detectar limites de la ventana
				this->location->y = TOP;
			}
			if(location->y < BOTTOM){/// detectar limites de la ventana
				this->location->y = BOTTOM;
			}
			
			if(location->x > HEIGHT){/// detectar limites de la ventana
				this->location->x = HEIGHT;
				
					
			}
			if(location->x < -HEIGHT){/// detectar limites de la ventana
				this->location->x = -HEIGHT;
				
			}
			
			}
		
		
		/*
		
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
		}else if(val>0 && num == 5){
			this->destroyAllEnemiesAndReset();
		} else if (val == 1 && num == 1){
			delete Joystick;
			end = true;
			exit(0);
		}*/
		
	//	std::cout<< location->x <<" - " <<location->y <<std::endl;
		
	};
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
				temp->decrement_hp();
				
				if(temp->get_hp() <= 0){
					temp->alive = false;
					
					bl = bullets[i];
					bullets.erase(bullets.begin() + i);
					i--;
					delete bl;
					deleted_bullet = true;
					
					//dropear un Item
					switch(temp->drop_item){
					case 1:{
						std::cout << "Drop Item 1" << std::endl;
						DoubleShotItem *power = new DoubleShotItem(temp->location->x,temp->location->y);
						items.push_back(power);
						break;
					}
					
					case 2:{
						std::cout << "Drop Item 2" << std::endl;
						DoubleBulletItem *power = new DoubleBulletItem(temp->location->x,temp->location->y);
						items.push_back(power);
						break;
					}
						
					case 3:{
						std::cout << "Drop Item 3" << std::endl;
						DoubleShotBulletItem *power = new DoubleShotBulletItem(temp->location->x,temp->location->y);
						items.push_back(power);
						break;
					}
						
					case 4:{
						std::cout << "Drop Item 4" << std::endl;
						HealthItem *power = new HealthItem(temp->location->x,temp->location->y);
						items.push_back(power);
						break;
					}
						
					case 5:{
						std::cout << "Drop Item 5" << std::endl;
						if(!this->hasBomb){
							SuperBombItem *power = new SuperBombItem(temp->location->x,temp->location->y);
							items.push_back(power);
						}
						break;
					}
						
					default:
						std::cout << "Drop Nothing" << std::endl;
					}
				}
				
			}

			if (!temp->alive && temp->bullets.size() <= 0){
				score += temp->iscore(); // increment score
				//cout<<"MATADO: "<<score<<endl;
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

void Player::checkItemCollision(){
	for(int i = 0;i<items.size();i++){
		//std::cout<<"distancia item "<<i<<this->location->distance(items[i]->location)<<std::endl;
		if(items[i]->location->y<-140){
			items[i]->active = false;
		}else if(this->location->distance(items[i]->location)<=COLLISION){
			items[i]->active = false;
			if(items[i]->id == 5){
				this->hasBomb = true;
			}else if(items[i]->id == 4){
				if(this->hp<5){
					this->hp++;
				}
				
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

void drawBitmapText(string s,float x,float y,float z) {  
	glRasterPos3f(x, y,z);
	
	for (int i=0; i<s.size(); i++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
	}
}

void Player::draw(){
	this->checkItemCollision();
	/// Vidas
	for(int i = 0; i<this->hp;i++){
		glPushMatrix();
			glColor3d(255, 255, 255);
			glTranslatef(-110.0f+i*10, -110.0f, 0.0f);
			glutSolidTeapot(4);
		glPopMatrix();
	}
	 
	/// Score
	glPushMatrix();
	string s = "Score: " + to_string(score);
	drawBitmapText(s,80,-110.0f,0);
	glPopMatrix();
	
	/// Jugador
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
