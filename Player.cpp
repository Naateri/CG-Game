#include "Player.h"

std::vector<Enemy*> enemies;
std::vector<Item *> items;

GLint health1[9];
GLint blue[7];
GLint red[7];
GLint green[7];
GLint yellow[7];
GLint enemy_bullets2;

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
		pair<float,float> control = Joystick->controls();
		
		if(Joystick->isButton){
			val = Joystick->value; 
			num = control.first;
			
			if (num == 0){
				shoot();
			}else if(num == 5){
				
				cout<<"BOMBA"<<endl;
				
				this->destroyAllEnemiesAndReset();
				
				
			} else if (num == 1 ){
			
				delete Joystick;
				end = true;
				exit(0);
			}
			else if(num == -1){
			
			}
			
		
			
			
		}
		else{
		
	
		//	cout<<"Controles: "<<control.first<<"   "<<control.second<<endl;
		
			if(control.first * DIFFERENCE > 0){
				cout<<"ROTAR DERECHA"<<endl;
				right = true;
				left = false;
			}
			else if(control.first * DIFFERENCE < 0){
				cout<<"ROTAR IZQUIERDA"<<endl;
				right = false;
				left = true;
			}
			else{
				right = false;
				left = false;
			}
			//this->location->x += control.first * DIFFERENCE;
			this->location->x += control.first * DIFFERENCE;
			//this->location->y -= control.second * DIFFERENCE;
			this->location->y -= control.second * DIFFERENCE;
			//cout<<"X esta en :"<<this->location->x<<endl;
			//cout<<"Y esta en :"<<this->location->y<<endl;
			
			
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
		
		
	};
}

	
void Player::destroyAllEnemiesAndReset(){
	if(this->hasBomb){
		std::cout<<"Boom\n";
		this->power = 0;
		enemies.clear();
		items.clear();
		bullets.clear();
		hasBomb = false;
	}
}

void Player::shoot(){
	if(this->power == 0){
		Bullet* bala = new Bullet(location->x,location->y);
		bullets.push_back(bala);
	}else if(this->power == 1){
		Bullet* bala1 = new Bullet(location->x-5,location->y);
		Bullet* bala2 = new Bullet(location->x+5,location->y);
		bullets.push_back(bala1);
		bullets.push_back(bala2);
	}else if(this->power == 2){
		Bullet* bala1 = new Bullet(location->x,location->y+10);
		Bullet* bala2 = new Bullet(location->x,location->y);
		bullets.push_back(bala1);
		bullets.push_back(bala2);
	}else if(this->power == 3){
		Bullet* bala1 = new Bullet(location->x-5,location->y+10);
		Bullet* bala2 = new Bullet(location->x+5,location->y+10);
		bullets.push_back(bala1);
		bullets.push_back(bala2);
		bala1 = new Bullet(location->x-5,location->y);
		bala2 = new Bullet(location->x+5,location->y);
		bullets.push_back(bala1);
		bullets.push_back(bala2);
	}
}



void Player::bullet_texture(float tam, int type){
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	
	if(type == 1){//amarillo
		glColor3d(255,255,0);
	}
	else if(type == 2){//verde
		glColor3d(0,1,255);
	}
	else if(type == 3){//rojo
		glColor3d(255,0,0);
	}
	else{//vida(corazon) y bomba(azul)
		glColor3d(255,0,255);
	}
	
	GLUquadricObj *quadricObj = gluNewQuadric();
	gluQuadricDrawStyle(quadricObj, GLU_FILL);
	
	glBindTexture(GL_TEXTURE_2D, fire);
	
	
	gluQuadricTexture(quadricObj, GL_TRUE);
	gluQuadricNormals(quadricObj, GLU_SMOOTH);
	
	gluSphere(quadricObj,tam,30,30);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void Player::loadTexture(){
	string tex1;
	///Vidas
	for(int i=1;i<9;++i){
		string name = "Health/frame-" + to_string(i) + ".png";
		//cout<<name<<endl;
		char const* name1 = name.c_str();
		salud[i] = TextureManager::Inst()->LoadTexture(name1, GL_BGRA_EXT, GL_RGBA);
		health1[i] = TextureManager::Inst()->LoadTexture(name1, GL_BGRA_EXT, GL_RGBA);
	}
	
	///Jugador
	tex1 = "texture_player.png";
	//cout<<tp<<endl;
	char const* texture1 = tex1.c_str();
	texture_player = TextureManager::Inst()->LoadTexture(texture1, GL_BGRA_EXT, GL_RGBA);

	
	///Items 
	for(int i=1;i<7;++i){
		string r = "Red/frame-" + to_string(i) + ".png";
		//cout<<r<<endl;
		char const* red1 = r.c_str();
		red[i] = TextureManager::Inst()->LoadTexture(red1 , GL_BGRA_EXT, GL_RGBA);
		

		string g = "Green/frame-" + to_string(i) + ".png";
		//cout<<g<<endl;
		char const* green1 = g.c_str();
		green[i] = TextureManager::Inst()->LoadTexture(green1 , GL_BGRA_EXT, GL_RGBA);
		
		string ye = "Yellow/frame-" + to_string(i) + ".png";
		//cout<<ye<<endl;
		char const* yellow1 = ye.c_str();
		yellow[i] = TextureManager::Inst()->LoadTexture(yellow1 , GL_BGRA_EXT, GL_RGBA);
		
		string b = "Blue/frame-" + to_string(i) + ".png";
		//cout<<b<<endl;
		char const* blue1 = b.c_str();
		blue[i] = TextureManager::Inst()->LoadTexture(blue1, GL_BGRA_EXT, GL_RGBA);
	}
	
	///Numeros
	for(int i=0;i<10;++i){
		string num = "Numbers/numeral" + to_string(i) + ".png";
		
		char const* number = num.c_str();
		numbers[i] = TextureManager::Inst()->LoadTexture(number, GL_BGRA_EXT, GL_RGBA);
	}
	
	
	///Bullets
	tex1 = "fuego.jpg";
	//cout<<tp<<endl;
	char const* f = tex1.c_str();
	fire = TextureManager::Inst()->LoadTexture(f, GL_BGR_EXT, GL_RGB);
	
	///Enemigo 1 
	tex1 = "verde1.jpg";
	//cout<<tp<<endl;
	char const* eb = tex1.c_str();
	enemy_bullets = TextureManager::Inst()->LoadTexture(eb, GL_BGR_EXT, GL_RGB);
	
	///Enemigo 2
	tex1 = "red.jpg";
	//cout<<tp<<endl;
	char const* eb2 = tex1.c_str();
	enemy_bullets2 = TextureManager::Inst()->LoadTexture(eb2, GL_BGR_EXT, GL_RGB);
	
	
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

void Player::drawScore(string s,float x,float y,float z) {  
	glEnable(GL_TEXTURE_2D);
	float h = 4;
	float w = 4;
	
	glPushMatrix();
	for (int i=s.size()-1; i>=0;i--){ 
		glPushMatrix();
		int idx = s[i]-48;
		
		glBindTexture(GL_TEXTURE_2D, numbers[idx]);
		
		glTranslatef(x+i*10,y,z);
		glRotatef(180,0,1,0);
		glTranslatef(0.0f,0.0f,0.0f);
		glBegin(GL_QUADS);
		glColor3f(1.0,1.0,1.0);
		
		glTexCoord2f(0,0);
		glVertex3d(w, -h, 0);
		
		glTexCoord2f(1,0);
		glVertex3d(-w, -h, 0);
		
		
		
		glTexCoord2f(1,1);
		glVertex3d(-w, h, 0);
		
		glTexCoord2f(0,1);
		glVertex3d(w, h, 0);
		
		
		glEnd();
		glPopMatrix();
		
	
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	
}


void Player::draw_bullets(){
	Bullet* bl;
	Enemy* temp;
	for(int i=0;i<bullets.size();++i){
		bool deleted_bullet = false;
		bullets[i]->location->y += 5;
		bullets[i]->rotation += 15.0f;
		glPushMatrix();
		if(this->power == 3){//verde
			this->collision = 5.0f;
			glTranslatef(bullets[i]->location->x, bullets[i]->location->y, 0.0f);
			glRotatef(bullets[i]->rotation, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f,0.0f,0.0f);
			bullet_texture(3.0f, this->power);
			
			
		}else{
			this->collision = 10.0f;
			glTranslatef(bullets[i]->location->x, bullets[i]->location->y, 0.0f);
			glRotatef(bullets[i]->rotation, 0.0f, 0.0f, 1.0f);
			glTranslatef(0.0f,0.0f,0.0f);
			bullet_texture(4.0f, this->power);
			
			
		}
		glPopMatrix();
		
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


void Player::draw_health(int i){
	i = i % 8; /// son 8 sprites de salud
	if(i==0){
		i+=1;
	}

	//cout<<"I " <<i<<endl;
	float h = 494/410*4;
	float w = 443/410*4;
	
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, salud[i]);
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
	glPopMatrix();
}


void Player::draw_player(){
	float h = 9;
	float w = 10;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_player);
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

string formatScore(string s){
	int num = s.size();
	
	
	if(num == 1)
		s = "000"+s;	
	else if (num ==2){
		s = "00"+s;
	}
	else if (num ==3){
		s = '0'+s;
	}
	return s;
}
	
void Player::draw(){
	
	
	time1 = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
	int delta = time1 -timebase;// delta time
	timebase = time1;
	anim += delta;//duracion de la animacion entre dos cambios de Sprite
	
	if (anim / 1000.0 > 0.15)// si el tiempo de animacion dura mas 0.15s cambiamos de sprite
	{
		i++;
		anim = 0.0;
	}
	
	

	
	this->checkItemCollision();
	/// Score
	
	glPushMatrix();
	string act_score = formatScore(to_string(score));
	drawScore(act_score,80,-110.0f,0);
	glPopMatrix();
	
	/// Vidas
	for(int h = 0; h<this->hp;h++){
		
		glPushMatrix();
			
			glTranslatef(-110.0f+h*10, -110.0f, 0.0f);
			draw_health(i);
		glPopMatrix();
		
	}
	 

	

	
	/// Jugador
	glPushMatrix();
	//glColor3d(255, 0, 255);
	
	
	glTranslatef(location->x, location->y, 0.0f);
	if(right){
		glRotatef(35, 0.0f, 1.0f, 0.0f);
	}
	else if(left){
		glRotatef(-35,0.0f, 1.0f, 0.0f);
	}
	glTranslatef(0.0f, 0.0f, 0.0f);
	draw_player();
	//glutSolidTeapot(10);
	glPopMatrix();
	
	///Bomba
	if(hasBomb){
		glPushMatrix();
		glColor3d(1,0,0);
		string b = "Bomb";
		//drawBitmapText(b,0,-110.0f,0);
		
		glPopMatrix();
	}
	
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

float Player::getY(){
	return location->y;
}
