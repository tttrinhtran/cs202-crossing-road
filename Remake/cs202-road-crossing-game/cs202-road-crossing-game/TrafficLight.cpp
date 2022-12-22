#include "TrafficLight.h"

void TrafficLight::initVariables()
{
	shape.setSize(sf::Vector2f(50.f, 50.f)); 
	shape.setFillColor(sf::Color::Red); 
}

TrafficLight::TrafficLight()
{
	initVariables(); 
}

TrafficLight::~TrafficLight(){}

sf::RectangleShape TrafficLight::getShape()
{
	return shape; 
}

void TrafficLight::setPosition(float x, float y)
{
	shape.setPosition(x, y); 
}

void TrafficLight::update(bool move)
{
	if (move && shape.getFillColor() == sf::Color::Green)
		shape.setFillColor(sf::Color::Red); 
	if (!move && shape.getFillColor() == sf::Color::Red)
		shape.setFillColor(sf::Color::Green); 
}

void TrafficLight::render(sf::RenderWindow& window)
{
	window.draw(shape);
}
