#include "Wood.h"

Wood::Wood()
{
	shape.setSize(sf::Vector2f(100.0f, 100.0f));
	texture.loadFromFile("pic/wood.png");
	shape.setTexture(&texture);
	texture.setSmooth(true);
}
