#include "Wood.h"

Wood::Wood()
{
	shape.setSize(sf::Vector2f(60.0f, 80.0f));
	texture.loadFromFile("pic/wood.png");
	shape.setTexture(&texture);
	texture.setSmooth(true);
	sound.openFromFile("sound/santa.ogg");
}

bool Wood::checkType()
{
	return false;
}