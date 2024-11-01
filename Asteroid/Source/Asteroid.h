#pragma once
#include "Screen.h"
#include "Bullet.h"
#include "Ship.h"
#include <vector>
#include<iostream>
class Asteroid
{
	float SpeedX;
	float SpeedY;
	float Angle;

public:
	float Size;
	Sprite Asteroidpic;	
	Vector2 position;
	float radius;

	Asteroid(Screen& screen, float size, float posX, float posY, float angle,float speedX,float speedY);

	void moving(Screen& screen);
	void drawasteroids(Screen& screen);
	void worldwrapping(Screen& screen);
	void hitbybullet(Screen& screen);
};
