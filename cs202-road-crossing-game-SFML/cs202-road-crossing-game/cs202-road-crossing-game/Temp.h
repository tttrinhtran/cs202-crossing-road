#pragma once
#include "Header.h"
class Temp
{
private: 
	sf::CircleShape shape;
	
	void initShape(const sf::RenderWindow& window, sf::Vector2f curPos); 
public: 
	Temp(const sf::RenderWindow& window, sf::Vector2f curPos);
	virtual ~Temp();

	const sf::CircleShape& getShape() const; 
	
	void setPosition(); 

	void update(); 
	void render(sf::RenderTarget* target); 
};

