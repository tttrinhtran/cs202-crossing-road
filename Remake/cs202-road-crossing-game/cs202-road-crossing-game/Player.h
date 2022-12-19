#pragma once
#include "Header.h"
class Player
{
private: 
	sf::RectangleShape shape;
	sf::Texture texture; 
	sf::Time time = sf::seconds(0.005f); 
	sf::Clock clock;
	const float movementSpeed = 10.f; 

	void initVariables(); 
public: 
	Player(); 
	virtual ~Player(); 

	sf::RectangleShape getshape(); 
	void reset(); 
	void updateInput(); 
	void updateWindowBoundsCollision(const sf::RenderTarget& target); 
	void update(sf::RenderWindow& window);
	void render(sf::RenderTarget& target); 
};

