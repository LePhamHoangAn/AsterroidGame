#include "Screen.h"
#include "UFO.h"

UFO::UFO(Screen& screen)	
{
	
	Up = true;
	
	UFOpic = screen.LoadSprite("assets/UFO.png");
	UFOpic.texture.src = { 0,0,50,42 };
	UFOpic.origin = { 25,21 };
	UFOpic.angle = 0;
	radius = UFOpic.texture.width/2;
}


void UFO::movement(Screen& screen)
{
	if (Up)
	{
		
		position.x += 1;
		position.y = 0+ UFOpic.texture.height;
	}
	else
	{
		
		position.x += 1;
		position.y = screen.GetWindowHeight() - UFOpic.texture.height;
	}
}

void UFO::worldwrapping(Screen& screen)
{
	if (position.x > screen.GetWindowWidth()+UFOpic.texture.width)
	{
		position.x = 0;
	}
}

void UFO::drawufo(Screen& screen)
{
	UFOpic.position = { position };
	screen.DrawSprite(UFOpic);
}

void UFO::shooting(Screen& screen)
{
	float cooldown = 1;
	if (timekeeperforshooting.getElapsedTime().asSeconds() >= cooldown)
	{
		int angle = 0;
		if (Up)
		{
			angle = 180;
		}
		else
		{
			angle = 0;
		}
		//get the pos and angle from the ship
		UFObullet ufobullet(screen, position.x, position.y, angle, 10);
		UFObullets.push_back(ufobullet);
		timekeeperforshooting.restart();
	}
	for (int i = 0; i < UFObullets.size(); i++)
	{
		UFObullets[i].movement(screen);
	}
}

