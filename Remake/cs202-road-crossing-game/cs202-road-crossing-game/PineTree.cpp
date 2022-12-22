#include "PineTree.h"

PineTree::PineTree()
{
	shape.setSize(sf::Vector2f(100.0f, 100.0f));
	texture.loadFromFile("pic/pinetree.png");
	shape.setTexture(&texture);
	texture.setSmooth(true);
}
