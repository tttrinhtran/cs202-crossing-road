#include "Candy.h"

Candy::Candy()
{
	shape.setSize(sf::Vector2f(100.0f, 100.0f));
	texture.loadFromFile("pic/candy.png");
	shape.setTexture(&texture);
	texture.setSmooth(true);
}
