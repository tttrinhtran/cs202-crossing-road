#include "Ginger.h"

Ginger::Ginger()
{
	shape.setSize(sf::Vector2f(100.0f, 100.0f));
	texture.loadFromFile("pic/ginger.png");
	shape.setTexture(&texture);
	texture.setSmooth(true);
	sound.openFromFile("sound/santa.ogg");
}
