#include "PineTree.h"

PineTree::PineTree()
{
	shape.setSize(sf::Vector2f(80.0f, 80.0f));
	texture.loadFromFile("pic/pinetree.png");
	shape.setTexture(&texture);
	texture.setSmooth(true);
	sound.openFromFile("sound/santa.ogg");
}
