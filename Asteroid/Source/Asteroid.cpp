#include "Asteroid.h"
#include<iostream>


Asteroid::Asteroid(Screen& screen, float size, float posX, float posY, float angle, float speedX,float speedY)
{
	Asteroidpic = screen.LoadSprite("assets/asteroid.png");
	position.x = posX;
	position.y = posY;
	Asteroidpic.texture.src = { 0,0,300,264 };
	Asteroidpic.origin = { 150,132 };
	Asteroidpic.scale = {size};
	radius = (Asteroidpic.texture.width / 2)*size;
	SpeedX = 1;
	SpeedY = 1;
	Angle = angle;
}

void Asteroid::moving(Screen& screen)
{
	position.x +=(float)sin((Angle * 3.14) / 180) * SpeedX;
	position.y -=(float)cos((Angle * 3.14) / 180) * SpeedY;
}

void Asteroid::drawasteroids(Screen& screen)
{
	Asteroidpic.position = { position };
	Asteroidpic.angle = Angle;
	screen.DrawSprite(Asteroidpic);
}

void Asteroid::worldwrapping(Screen& screen)
{
	if (position.x > screen.GetWindowWidth() )
	{
		position.x = 0 ;
	}
	if (position.x < 0 )
	{
		position.x = screen.GetWindowWidth() ;
	}
	if (position.y > screen.GetWindowHeight() )
	{
		position.y = 0 ;
	}
	if (position.y < 0 )
	{
		position.y = screen.GetWindowHeight() ;
	}
}


