#pragma once
#include "Header.h"
class Player
{
private: 
	sf::Texture texture; 
	sf::Sprite sprite; 
	
	float movementSpeed; 
	int hp; int hpMax; 

	void initSanta(); 
	void initVariables();
public: 
	Player(); 
	virtual ~Player(); 

	const int& getHP() const; 
	const int& getHPMax() const; 

	void updateInput(); 
	void updateWindowBoundsCollision(const sf::RenderTarget& target); 
	void update(sf::RenderTarget& target);

	void render(sf::RenderTarget& target);
};