#include "Item.h"

//vector<GLint> health1;

HealthItem::HealthItem(int x, int y) {
	this->id = 4;
	this->location = new Point2D(x,y);
	

	
}

void HealthItem::draw_item(int idx){
	idx = idx % 8; /// son 8 sprites de salud
	if(idx==0){
		idx+=1;
	}

	float h = 6;
	float w = 6;
	
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, health1[idx]);
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

void HealthItem::draw(){
	time1 = glutGet(GLUT_ELAPSED_TIME); // recupera el tiempo ,que paso desde el incio de programa
	int delta = time1 -timebase;// delta time
	timebase = time1;
	anim += delta;//duracion de la animacion entre dos cambios de Sprite
	
	if (anim / 1000.0 > 0.15)// si el tiempo de animacion dura mas 0.15s cambiamos de sprite
	{
		i++;
		anim = 0.0;
	}
	
	if(this->active){
		glPushMatrix();
		glTranslatef(location->x, location->y, 0.0f);
		draw_item(i);
		glPopMatrix();
	}
}

void HealthItem::move(){
	if(this->active){
		location->y -= HEALTH_ITEM_SPEED;
	}
}
