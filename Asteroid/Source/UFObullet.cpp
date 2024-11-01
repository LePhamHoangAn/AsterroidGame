#include "UFObullet.h"

UFObullet::UFObullet(Screen& screen, float posX, float posY, float angle, float speed)
{
	Speed = speed;
	UFObulletpic = screen.LoadSprite("assets/UFOlaser.png");
	UFObulletpic.texture.src = { 0,0,6,24 };
	UFObulletpic.origin = { 3,12 };
	UFObulletpic.angle = angle;
	position.x = posX;
	position.y = posY;
	radius = UFObulletpic.texture.width / 2;
	//put in the constructor so it wont change
	v.x = -sin(((UFObulletpic.angle) * 3.14) / 180);
	v.y = cos(((UFObulletpic.angle) * 3.14) / 180);
}

void UFObullet::movement(Screen& screen)
{
	position.x -= (v.x * Speed);
	position.y -= (v.y * Speed);
}

void UFObullet::drawbullet(Screen& screen)
{
	UFObulletpic.position = { position };
	screen.DrawSprite(UFObulletpic);
}