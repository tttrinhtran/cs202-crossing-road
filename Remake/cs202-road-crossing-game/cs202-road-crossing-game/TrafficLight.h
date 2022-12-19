#pragma once
#include "Header.h"
class TrafficLight
{
private: 
	sf::RectangleShape shape; 

	void initVariables(); 
public: 
	TrafficLight(); 
	virtual ~TrafficLight(); 

	sf::RectangleShape getShape(); 
	
	void setPosition(float x, float y); 
	void update(bool canMove); 
	void render(sf::RenderTarget& target); 
};

