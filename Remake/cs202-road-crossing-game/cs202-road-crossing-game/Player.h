#pragma once
#include "Header.h"
class Player
{
private: 
	sf::RectangleShape shape;
	sf::Texture texture; 
	sf::Time time = sf::seconds(0.05f); 
	sf::Clock clock;
    	sf::Texture texturebg;
    	sf::Sprite bg;
	const float movementSpeed = 50.f; 
	void initVariables(); 
public: 
	Player(); 
	virtual ~Player(); 

	sf::RectangleShape getshape(); 
	void reset(int laneCount); 
	void updateInput(); 
	void updateWindowBoundsCollision(const sf::RenderWindow& window); 
	void update(sf::RenderWindow& window);
	void render(sf::RenderWindow& window); 
};

