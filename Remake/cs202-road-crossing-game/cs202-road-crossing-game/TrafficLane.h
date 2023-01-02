#pragma once
#include "Header.h"
#include "TrafficLight.h"
#include "Obstacle.h"

#define lane_limit 7

class TrafficLane
{
private:
	float timer = 20.f; 
	float timeSpawning = 20.f; 
	int speed = 1;
	int spawnRate = 1;
	int laneCount = 5;

	std::vector<TrafficLight*> trafficLight; 
	std::vector<Obstacle*> obs; 
	std::vector<int> light;
	std::vector<bool> traffic;
	
	sf::Clock clock; 

	int lane = 0; 


	void initVariable(); 
public: 
	TrafficLane(); 
	virtual ~TrafficLane(); 

	bool canMove(int lane); 
	void update(sf::RenderWindow& window, int level);
	void Attr_Change(int attr);
	void spawnEnemy(sf::RenderWindow& window);

	void renderObstacle(sf::RenderWindow& window);
	void renderTrafficLight(sf::RenderWindow& window); 
	void render(sf::RenderWindow& window);
	bool Collision(sf::FloatRect coll); 
	void resetTimer(); 

	friend class Game;
};
