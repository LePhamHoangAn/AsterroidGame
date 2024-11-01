#pragma once
#include "Screen.h"
#include <vector>
class Bullet
{	
    float Angle;
    float Speed;
	Vector2 v;
	
public:
	Vector2 position;
	float radius;
	Sprite bullet;
	Bullet(Screen& screen, float posX, float posY, float angle, float speed);
	void drawbullet(Screen& screen);
	void flying(Screen& screen);
	void destroybullets(Screen& screen);
};


