#pragma once
#include "Screen.h"
#include "Ship.h"
#include <string>

class GUI
{
	int lives;

public:
	int score;

	GUI(Screen& screen);
	Sprite heart1;
	Sprite heart2;
	Sprite heart3;
	void takedamage(int damage);
	void livesmanager(Screen& screen);
	bool gameover();
	void gamescore(Screen& screen);
};