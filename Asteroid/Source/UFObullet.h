#pragma once
#include"screen.h"


class UFObullet
{
	Sprite UFObulletpic;
	Vector2 v;
	float Speed;

public:
	Vector2 position;
	float radius;
	UFObullet(Screen& screen, float posX, float posY, float angle, float speed);
	void movement(Screen& screen);
	void drawbullet(Screen& screen);
};