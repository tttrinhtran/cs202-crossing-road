#include "Obstacle.h"

void Obstacle::initObstacle()
{
	if (!texture.loadFromFile("pic/shiba.png"))
		std::cout << "Load obstacle failed\n";
	sprite.setTexture(texture);
	sprite.setScale(0.3f, 0.3f);
}

Obstacle::Obstacle(sf::Vector2f pos,sf::RenderWindow& window)
{
	initObstacle();
	float x = pos.x, y = pos.y; 
	if (x >= window.getSize().x + 100.f) x = 0.f;
	else x += 100.f; 
	sprite.setPosition(x, y);
}

Obstacle::~Obstacle()
{

}

const sf::Sprite& Obstacle::getSprite() const
{
	return this->sprite;
}

void Obstacle::update()
{

}

void Obstacle::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}
