#pragma once
#include "Header.h"
class Obstacle
{
protected: 
	sf::Vector2f speed; 
	sf::RectangleShape shape; 
	sf::Texture texture; 

	sf::Music sound; 
	friend class TrafficLane; 
public: 
	sf::RectangleShape getShape(); 

	void update(); 
	void setPosition(sf::Vector2f pos);
	void setSpeed(float x, float y); 
	void render(sf::RenderWindow& window);
	void setSize(sf::Vector2f size); 
	void makeSound(); 
	virtual bool checkType(); 
};

