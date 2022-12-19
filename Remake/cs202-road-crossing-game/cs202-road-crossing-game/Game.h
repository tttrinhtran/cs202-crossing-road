#pragma once
#include "Header.h"
#include "TrafficLane.h"
#include "Obstacle.h"
#include "Player.h"
class Game
{
private: 
	sf::Event event; 

	TrafficLane* trafficLane; 
	Player* player; 

	bool isRunning; 

	void initVariables(); 
	
	int level; 
	bool pause; 
	bool win; 

public:
	Game(); 
	virtual ~Game(); 

	void pollEvents(sf::RenderWindow& window); 


	int runGame(sf::RenderWindow& window);

	void setLevel(const int& level);

	int getLevel();
	bool isWin(); 
	void drawNextLevel(sf::RenderWindow& window); 

	void update(sf::RenderWindow& window); 
	void render(sf::RenderWindow& window); 
};

