#include "Reindeer.h"

Reindeer::Reindeer()
{
	shape.setSize(sf::Vector2f(75.0f, 90.0f));
	texture.loadFromFile("pic/reindeer.png");
	shape.setTexture(&texture);
	texture.setSmooth(true);
	sound.openFromFile("sound/santa.ogg");
}

bool Reindeer::checkType()
{
	return true;
}
