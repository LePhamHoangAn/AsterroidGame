#pragma once
#include "Screen.h"
#include"Bullet.h"
#include<vector>
#include "SFML/System/Clock.hpp"

class Ship
{
	bool boost;
	bool shooting;
	bool teleport;
	bool turningleft;
	bool turningright;
	Vector2 dir;

public:
	Vector2 position;
	float Angle;
	float radius;

	Sprite ship;
	Sound shipshoot;
	Sound shiptele;
	Sound shipthrust;

	sf::Clock timekeeperforshooting;
	sf::Clock timekeeperfortele;

	std::vector<Bullet>Bullets;

	Ship(Screen& screen);

	void respawn(Screen&screen);
	void worldwrapping(Screen& screen);
	void drawship(Screen& screen);
	void input(Screen& screen);
	void movement(Screen& screen);
	void shoot(Screen& screen);
};
