#include "Bullet.h"

#include <iostream>
#include <vector>


Bullet::Bullet(Screen&screen, float posX,float posY, float angle,float speed)
{
	Speed=speed;
	bullet = screen.LoadSprite("assets/laser.png");
	bullet.texture.src = { 0,0,6,24 };
	bullet.origin = { 3,12 };
	bullet.angle = angle;                                   
	position.x = posX;
	position.y = posY;
	radius = bullet.texture.width / 2;
//put in the constructor so it wont change
	v.x = -sin(((bullet.angle) * 3.14) / 180);
	v.y = cos(((bullet.angle) * 3.14) / 180);
}

void Bullet::drawbullet(Screen& screen)
{
	bullet.position = { position };	
	screen.DrawSprite(bullet);
}


void Bullet::flying(Screen& screen)
{
	position.x -= (v.x * Speed);
	position.y -= (v.y * Speed);
}

void Bullet::destroybullets(Screen& screen)
{
	if (position.x > 1500 || position.x < -500 || position.y>1500 || position.y < -500)
	{

	}
}