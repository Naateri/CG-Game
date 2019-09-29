#ifndef POINT_H
#define POINT_H

#include <GL/glut.h>
#include <math.h>

struct Point2D{
	float x,y;
	Point2D(float x, float y){
		this->x = x; this->y = y;
	}
	void draw(){
		glPointSize(10);
		glBegin(GL_POINTS);
		glVertex2f(x,y);
		glEnd();
	}
	double distance(Point2D* b){
		return sqrt( pow(this->x - b->x, 2) + pow(this->y - b->y, 2) );
	}
};

struct Point3D{
	int x,y,z;
	Point3D(int x, int y, int z){
		this->x = x; this->y = y; this->z = z;
	}
};

#endif
