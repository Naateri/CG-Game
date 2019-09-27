#include <GL/glut.h>


struct Point2D{
	int x,y;
	Point2D(int x, int y){
		this->x = x; this->y = y;
	}
	void draw(){
		glPointSize(10);
		glBegin(GL_POINTS);
		glVertex2f(x,y);
		glEnd();
	}
};

struct Point3D{
	int x,y,z;
	Point3D(int x, int y, int z){
		this->x = x; this->y = y; this->z = z;
	}
};
