#pragma once
#include "Header.h"
class Obstacle
{
protected: 
	sf::Vector2f speed; 
	sf::RectangleShape shape; 
	sf::Texture texture; 

	friend class TrafficLane; 
public: 
	sf::RectangleShape getShape(); 

	void update(); 
	void setSpeed(float x, float y); 
	void render(sf::RenderTarget& target); 
};

