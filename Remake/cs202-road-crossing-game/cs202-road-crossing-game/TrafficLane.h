#pragma once
#include "Header.h"
#include "TrafficLight.h"
#include "Obstacle.h"
class TrafficLane
{
private:
	float timer = 20.f; 
	float timeSpawning = 20.f; 

	std::vector<TrafficLight*> trafficLight; 
	std::vector<Obstacle*> obs; 
	std::vector<int> light; 
	
	sf::Clock clock; 

	int lane = 0; 
	bool traffic[5] = { 0,0,0,0,0 };


	void initVariable(); 
public: 
	TrafficLane(); 
	virtual ~TrafficLane(); 

	bool canMove(int lane); 
	void update(sf::RenderWindow& window, int level); 
	void spawnEnemy(); // 

	void renderObstacle(sf::RenderTarget& target); 
	void renderTrafficLight(sf::RenderTarget& target); 
	void render(sf::RenderTarget& target);
	bool Collision(sf::FloatRect coll); 
	void resetTimer(); 
};

