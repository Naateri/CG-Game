#include "Meteors.h"

GLint texture_meteor;

Meteor::Meteor(Player* p){
	this->move_to = new Point2D(0.0f, 0.0f);
	this->move_to->x = (p->location->x - 100.0f);
	this->move_to->y = (p->location->y - 100.0f);
	
	float vec_normal = sqrt(pow(move_to->x, 2) + pow(move_to->y, 2));
	this->move_to->x /= vec_normal;
	this->move_to->y /= vec_normal;
	
	this->position = new Point2D(100.0f, 100.0f);
	
	this->p = p;
}

void Meteor::move(){
	this->position->x += (move_to->x * METEOR_SPEED);
	this->position->y += (move_to->y * METEOR_SPEED);
}

void draw_meteor(){
	glEnable(GL_TEXTURE_2D);
	GLUquadricObj *quadricObj = gluNewQuadric();
	gluQuadricDrawStyle(quadricObj, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, meteor_texture);
	glColor3d(71,75,78);
	gluQuadricTexture(quadricObj, GL_TRUE);
	gluQuadricNormals(quadricObj, GLU_SMOOTH);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	gluSphere(quadricObj,15,30,30);
	glDisable(GL_TEXTURE_2D);

}
void Meteor::draw(){
	glPushMatrix();
		glTranslatef(position->x, position->y, 0.0f);
		glRotatef(rotation, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 0.0f, 0.0f);
		draw_meteor();
	glPopMatrix();
	rotation += ROTATION_SPEED;	
}

bool Meteor::player_collision(){
	if (position->distance(p->location) <= METEOR_PLAYER_COLLISION){
		return true;
	} else return false;
}
