#pragma once
#include "Screen.h"
#include "SFML/System/Clock.hpp"
#include "UFObullet.h"
#include<vector>


class UFO
{
	
	Sprite UFOpic;
	
public:
	std::vector<UFObullet>UFObullets;
	Vector2 position;
	float radius;
	sf::Clock timekeeperforshooting;
	UFO(Screen& screen);
	bool Up;
	void movement(Screen& screen);
	void worldwrapping(Screen& screen);
	void drawufo(Screen& screen);
	void shooting(Screen& screen);
	
};