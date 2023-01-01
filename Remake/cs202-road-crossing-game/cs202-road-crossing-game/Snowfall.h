#pragma once
#include "Header.h"
#include "Obstacle.h"
class Snowfall; 
class Snow : public Obstacle
{
private: 
public: 
	Snow(); 
	friend class Snowfall; 
};

class Snowfall
{
private: 
	float timer = 20.0f;
	float timeSpawning = 20.0f;
	std::vector<Snow*> snow;
	sf::Clock clock;
public:
	void spawn();
	void render(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
};

