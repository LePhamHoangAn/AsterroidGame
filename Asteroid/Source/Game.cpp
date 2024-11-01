//#include <iostream>
#include"Game.h"

Game::Game(Screen& screen) :ship(screen), gui(screen), ufo(screen)
{
	Setup(screen);
	ship.respawn(screen);
	explosion = screen.LoadSound("assets/shipboom.ogg");
	explosion.volume = { 50 };

	explosionufo = screen.LoadSound("assets/boom.wav");
	explosionufo.volume = { 50 };

	explosionasteroid = screen.LoadSound("assets/boom1.wav");
	explosionasteroid.volume = { 50 };

	Theme = screen.LoadSound("assets/theme.wav");
	Theme.volume = { 100 };
	Theme.looping = true;
}

void Game::Setup(Screen& screen)
{
	int asteroidcount = 3;
	//asteroids	

	//waves
	if (gui.score >2500)
	{
		asteroidcount++ ;
	}
	if (gui.score > 7000)
	{
		asteroidcount++;
	}
	if (gui.score > 10000)
	{
		asteroidcount++;
	}
	if (gui.score > 15000)
	{
		asteroidcount++;
	}
		for (int i = 0; i < asteroidcount; i++)
		{
			float posX = rand()%500-screen.GetWindowWidth();
			float posY = rand() %500- screen.GetWindowHeight();
			float speedX = rand() % 5;
			float speedY = rand() % 5;
			float angle = rand() % 360;
			Asteroid asteroid(screen, 1, posX, posY, angle,speedX,speedY);
			asteroids.push_back(asteroid);
		}
}

void Game::drawasteroids(Screen& screen)
{
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].drawasteroids(screen);
	}
}

void Game::drawGUI(Screen& screen)
{
	gui.livesmanager(screen);
	gui.gamescore(screen);
}


void Game::shipbulletscollideasteroidandsplitting(Screen& screen)
{
	for (int j = asteroids.size() - 1; j >= 0; j--)
	{
		for (int i = ship.Bullets.size() - 1; i >= 0; i--)
		{
			if ((ship.Bullets[i].position - asteroids[j].position).Magnitude() < asteroids[j].radius + ship.Bullets[i].radius)
			{
				for (int i = 0; i < 2; i++)
				{
					float angle = asteroids[j].Asteroidpic.angle+rand()%60-60;
					float speedX = rand() % 5;
					float speedY = rand() % 5;
					Asteroid asteroid1(screen, asteroids[j].Asteroidpic.scale * 0.55f, asteroids[j].position.x, asteroids[j].position.y, angle, speedX, speedY);
					if (asteroid1.Asteroidpic.scale > 0.2f)
					{
						asteroids.push_back(asteroid1);
					}						
				}
				ship.Bullets.erase(ship.Bullets.begin() + i);
				asteroids.erase(asteroids.begin() + j);
				screen.PlaySound(explosionasteroid);
				gui.score += 100;
				break;
			}
		}
	}
}

void Game::bulletscleanup(Screen& screen)
{

	for (int i = ship.Bullets.size() - 1; i >= 0; i--)
	{						
			if (ship.Bullets[i].position.x > 1500 || ship.Bullets[i].position.x < -500 || ship.Bullets[i].position.y>1500 || ship.Bullets[i].position.y < -500)
			{
				ship.Bullets.erase(ship.Bullets.begin() + i);
			}
	}
	for (int i = ufo.UFObullets.size() - 1; i >= 0; i--)
	{
		if (ufo.UFObullets[i].position.y>1500 || ufo.UFObullets[i].position.y < -500)
		{
			ufo.UFObullets.erase(ufo.UFObullets.begin() + i);
		}
	}
	
}

void Game::shipcollideufo(Screen& screen)
{
	if ((ship.position - ufo.position).Magnitude() < ufo.radius + ship.radius)
	{
		screen.PlaySound(explosion);
		ship.respawn(screen);
		gui.takedamage(1);
	}
}

void Game::shipcollideasteroid(Screen& screen)
{
	for (Asteroid& asteroid : asteroids)
	{
		if ((ship.position - asteroid.position).Magnitude() < asteroid.radius + ship.radius)
		{
			screen.PlaySound(explosion);
			ship.respawn(screen);
			gui.takedamage(1);
		}
	}

}

void Game::shipbulletscollideufo(Screen& screen)
{
	for (int i = 0; i < ship.Bullets.size(); i++)
	{
		if ((ship.Bullets[i].position - ufo.position).Magnitude() < ufo.radius + ship.Bullets[i].radius&&ufo.Up==true)
		{
			screen.PlaySound(explosionufo);
			ufo.Up = false;
			gui.score += 100;
		}
		else if ((ship.Bullets[i].position - ufo.position).Magnitude() < ufo.radius + ship.Bullets[i].radius && ufo.Up == false)
		{
			screen.PlaySound(explosionufo);
			ufo.Up = true;
			gui.score += 100;
		}
	}
}

void Game::shipscollideufobullets(Screen& screen)
{
	for (int i = 0; i < ufo.UFObullets.size(); i++)
	{
		if ((ship.position - ufo.UFObullets[i].position).Magnitude() < ufo.UFObullets[i].radius + ship.radius)			
		{
			screen.PlaySound(explosion);
			ship.respawn(screen);
			gui.takedamage(1);
		}
	}
}

void Game::update(Screen& screen)
{
	//INPUT
	ship.input(screen);

	if (!gui.gameover())
	{
		screen.PlaySound(Theme);
		//LOGIC
		if (asteroids.empty())
		{
			Game::Setup(screen);
		}

		ship.movement(screen);
		ship.shoot(screen);
		ship.worldwrapping(screen);
		ufo.movement(screen);
		ufo.worldwrapping(screen);
		ufo.shooting(screen);
		Game::shipbulletscollideufo(screen);
		Game::shipbulletscollideasteroidandsplitting(screen);
		Game::shipscollideufobullets(screen);
		Game::shipcollideasteroid(screen);
		Game::shipcollideufo(screen);
		Game::bulletscleanup(screen);

		for (Asteroid& asteroid : asteroids)  //for each asteroid in the vector 
		{
			asteroid.worldwrapping(screen);
			asteroid.moving(screen);
		}

		//DRAW
		for (int i = 0; i < ship.Bullets.size(); i++)
		{
			ship.Bullets[i].drawbullet(screen);
			/*std::cout << ship.Bullets.size() << std::endl;*/
		}
		for (int i = 0; i < ufo.UFObullets.size(); i++)
		{
			ufo.UFObullets[i].drawbullet(screen);
			/*std::cout << ufo.UFObullets.size() << std::endl;*/
		}
		ufo.drawufo(screen);
		ship.drawship(screen);
		Game::drawasteroids(screen);
		Game::drawGUI(screen);		
		
	}
	else
	{
		screen.DrawText(screen.GetWindowWidth() / 2, screen.GetWindowHeight() / 2, 255, 0, 0, 255, "YOU LOSE");
		gui.gamescore(screen);
	}
}


