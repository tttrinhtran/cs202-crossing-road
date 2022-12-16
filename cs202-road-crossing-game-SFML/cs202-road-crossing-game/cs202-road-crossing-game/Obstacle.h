#pragma once
#include "Header.h"
class Obstacle
{
private:
	sf::Texture texture; 
	sf::Sprite sprite; 

	void initObstacle(); 
public: 
	Obstacle(sf::Vector2f pos, sf::RenderWindow& window); 
	virtual ~Obstacle(); 

	const sf::Sprite& getSprite() const; 
	void update(); 
	void render(sf::RenderTarget& target);
};

