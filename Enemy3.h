#ifndef ENEMY3_H
#define ENEMY3_H
#include "Enemy.h"

class Enemy3 : public Enemy {
public:
	Enemy3();
	void shoot ( );
	void draw ( );
	void move ( );
	float get_hp ( );
	void decrement_hp ( );
	float iscore ( );
protected:
	void draw_bullets ( );
private:
};

#endif

