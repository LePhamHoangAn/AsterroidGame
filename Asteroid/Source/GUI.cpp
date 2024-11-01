#include"GUI.h"

GUI::GUI(Screen& screen)
{
	heart1 = screen.LoadSprite("assets/heart.png");
	heart1.texture.src = { 0,0,50,50 };
	heart1.origin = { 25,25 };
	heart1.angle = 0;
	heart1.position = { 100,30 };

	heart2 = screen.LoadSprite("assets/heart.png");
	heart2.texture.src = { 0,0,50,50 };
	heart2.origin = { 25,25 };
	heart2.angle = 0;
	heart2.position = { 150,30 };

	heart3 = screen.LoadSprite("assets/heart.png");
	heart3.texture.src = { 0,0,50,50 };
	heart3.origin = { 25,25 };
	heart3.angle = 0;
	heart3.position = { 200,30 };

	lives = 3;
	score = 0;
}

void GUI::livesmanager(Screen& screen)
{
	if (lives == 3)
	{
		screen.DrawSprite(heart1);
		screen.DrawSprite(heart2);
		screen.DrawSprite(heart3);
	}
	if (lives == 2)
	{
		screen.DrawSprite(heart1);
		screen.DrawSprite(heart2);
	}
	if (lives == 1)
	{
		screen.DrawSprite(heart1);
	}
}

void GUI::takedamage(int damage)
{
	lives -= damage;
}

bool GUI::gameover()
{
	if (lives <= 0)
	{
		return true;
    }
	else
	{
		return false;
	}
}

void GUI::gamescore(Screen& screen)
{
	std::string Score = std::to_string(score);
	screen.DrawText(screen.GetWindowWidth()-200, 20, 255, 255, 255, 155, std::string("Score " + Score));
}
