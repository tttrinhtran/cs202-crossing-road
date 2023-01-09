#pragma once
#include "Header.h"
#include "TrafficLane.h"
#include "Obstacle.h"
#include "Player.h"
#include "Snowfall.h"
class Game
{
private: 
	sf::Event event; 

	TrafficLane* trafficLane; 
	Player* player; 

	bool isRunning; 
	Snowfall snowfall;
	void initVariables(); 
	
	int level; 
	bool pause; 
	bool win; 

	bool unexpectedExit;

public:
	Game(); 
	virtual ~Game(); 

	void pollEvents(sf::RenderWindow& window); 


	int runGame(sf::RenderWindow& window);

	void setLevel(const int& level);

	int getLevel();
	bool isWin(); 
	void drawWin(sf::RenderWindow& window);
	void drawNextLevel(sf::RenderWindow& window); 
	
	void update(sf::RenderWindow& window); 
	void renderLevel(sf::RenderWindow& window); 
	void render(sf::RenderWindow& window); 
};

// #include "Game.cpp"