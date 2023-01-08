#include "Ginger.h"

Ginger::Ginger()
{
	shape.setSize(sf::Vector2f(80.0f, 80.0f));
	texture.loadFromFile("pic/ginger.png");
	shape.setTexture(&texture);
	texture.setSmooth(true);
	sound.openFromFile("sound/santa.ogg");
}

bool Ginger::checkType()
{
	return false;
}
