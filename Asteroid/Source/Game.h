#pragma once

#include"Ship.h"
#include"Screen.h"
#include "Asteroid.h"
#include"Bullet.h"
#include"UFO.h"
#include"GUI.h"
#include<vector>
#include<iostream>


class Game
{
	
	Ship ship;
	GUI gui;
	UFO ufo;

	Sound explosion;
	Sound explosionufo;
	Sound explosionasteroid;
	Sound Theme;
	std::vector<Asteroid>asteroids;
public:
	
	Game(Screen& screen);

	void Setup(Screen& screen);

	void drawasteroids(Screen& screen);
	void drawGUI(Screen& screen);

	void bulletscleanup(Screen& screen);
	
	void shipbulletscollideufo(Screen& screen);
	void shipscollideufobullets(Screen& screen);
	void shipcollideasteroid(Screen& screen);
	void shipcollideufo(Screen& screen);

	void shipbulletscollideasteroidandsplitting(Screen& screen);

	void update(Screen& screen);
	
};

