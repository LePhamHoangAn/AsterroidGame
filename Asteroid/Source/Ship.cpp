

#include"Ship.h"
#include<iostream>

Ship::Ship(Screen& screen)	
{
	boost = false;
	shooting = false;
	teleport = false;
	turningleft = false;
	turningright = false;

	ship = screen.LoadSprite("assets/SHIPpic.png");
	ship.texture.src = { 0,0,50,50 };
	ship.origin = { 25,25};
	Angle = 90;
	ship.angle = Angle;

	shipshoot= screen.LoadSound("assets/shoot.wav");
	shipshoot.volume = { 50 };
	shiptele= screen.LoadSound("assets/tele.wav");
	shiptele.volume = { 50 };
	shipthrust = screen.LoadSound("assets/thrust.wav");
	shipthrust.volume = { 100 };

  	radius = ship.texture.width / 2;
	
}

void Ship::input(Screen& screen)
{
	if (screen.IsKeyDown(Key::Left))
	{
		turningleft = true;
	}
	else
	{
		turningleft = false;
	}

	if (screen.IsKeyDown(Key::Right))
	{
		turningright = true;
	}
	else
	{
		turningright = false;
	}

	
	if (screen.IsKeyDown(Key::Space))
	{
		shooting = true;
		
	}
	else
	{
		shooting = false;
	}
	
	
	
	if (screen.IsKeyDown(Key::Up))
	{
		boost = true;
	}
	else
	{
		boost = false;

	}
	if (screen.IsKeyDown(Key::Q))
	{
		teleport = true;
	}
	else
	{
		teleport = false;
	}
}


void Ship::movement(Screen& screen)
{
	if (turningleft==true)
	{
		Angle=Angle-2;
		if (Angle <= 0)
		{
			Angle = 359;
		}
	}
	
	if (turningright==true)
	{
		Angle=Angle+2;
		if (Angle >=360)
		{
			Angle = 1;
		}
	}
	
	ship.angle = Angle;


	if (boost)
	{
		screen.PlaySound(shipthrust);
		dir.y += ((float)sin((Angle) * 3.14 / 180) * 0.3f);
		dir.x += ((float)cos((Angle) * 3.14 / 180) * 0.3f);
	}
	else
	{
		screen.StopSound(shipthrust);
		dir.x *= 0.99f;
		dir.y *= 0.99f;
		
	}
	if (teleport)
	{
		screen.PlaySound(shiptele);
		float cooldown = 0.3;
		if (timekeeperfortele.getElapsedTime().asSeconds() >= cooldown)
		{
			
			position.x = rand() % screen.GetWindowWidth();
			position.y = rand() % screen.GetWindowHeight();
			timekeeperfortele.restart();
		}		
	}	
	position = position + dir;
}

void Ship::worldwrapping(Screen& screen)
{
	if (position.x > screen.GetWindowWidth() + ship.texture.src.w)
	{
		position.x = 0 - ship.texture.src.w;
	}
	if (position.x < 0 - ship.texture.src.w)
	{
		position.x = screen.GetWindowWidth() + ship.texture.src.w;
	}
	if (position.y > screen.GetWindowHeight() + ship.texture.src.h)
	{
		position.y = 0 - ship.texture.src.h;
	}
	if (position.y < 0 - ship.texture.src.h)
	{
		position.y = screen.GetWindowHeight() + ship.texture.src.w;
	}
}

void Ship::shoot(Screen& screen)
{	
	if (shooting)
	{
		float cooldown = 0.5;
		if (timekeeperforshooting.getElapsedTime().asSeconds() >= cooldown)
		{
			//get the pos and angle from the ship
			screen.PlaySound(shipshoot);
			Bullet bullet(screen, ship.position.x, ship.position.y, ship.angle-270,10);
			Bullets.push_back(bullet);
			timekeeperforshooting.restart();
		}	
		
	}
	else
	{
		screen.StopSound(shipshoot);
	}
	//make them fly
	for (int i = 0; i < Bullets.size(); i++)
	{
		Bullets[i].flying(screen);
	}
}

void Ship::respawn(Screen& screen)
{
	position.x = screen.GetWindowWidth() / 2;
	position.y = screen.GetWindowHeight() / 2;
}


void Ship::drawship(Screen& screen)
{
	ship.position = { position };
	ship.angle = Angle+90;
	screen.DrawSprite(ship);
}