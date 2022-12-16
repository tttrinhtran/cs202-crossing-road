#include "Temp.h"

void Temp::initShape(const sf::RenderWindow& window, sf::Vector2f curPos)
{
	shape.setRadius(5.f); 
	shape.setFillColor(sf::Color::Red);
	float x = curPos.x, y = curPos.y;
	if (x >= window.getSize().x + 100.f) x = 0.f;
	else x += 100.f;
	shape.setPosition(x, y);
}

Temp::Temp(const sf::RenderWindow& window, sf::Vector2f curPos)
{
	initShape(window, curPos);
}

Temp::~Temp()
{

}

const sf::CircleShape& Temp::getShape() const
{
	// TODO: insert return statement here
	return shape; 
}

void Temp::setPosition()
{
	float t = shape.getPosition().x; 
	shape.setPosition(t + 30.f, shape.getPosition().y);
}

void Temp::update()
{
	
}

void Temp::render(sf::RenderTarget* target)
{
	target->draw(shape);
}
