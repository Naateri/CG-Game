#include "Item.h"

//vector<GLint> blue;


SuperBombItem::SuperBombItem(int x, int y) {
	this->id = 5;
	this->location = new Point2D(x,y);


}

void SuperBombItem::draw_item(int idx){
	idx = idx % 6; /// son 6 sprites de item
	if(idx==0){
		idx+=1;
	}
	
	float h = 6;
	float w = 6;
	
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, blue[idx]);
	
	glBegin(GL_QUADS);
		glColor3f(1.0,1.0,1.0);
		
		glTexCoord2f(1,0);
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


void SuperBombItem::draw(){
	
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

void SuperBombItem::move(){
	if(this->active){
		location->y -= SUPER_BOMB_SPEED;
	}
}
