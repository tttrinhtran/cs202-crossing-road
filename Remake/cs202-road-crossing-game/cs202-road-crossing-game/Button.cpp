#include "Button.h"

Button::Button() {}

Button::~Button() {}

Button::Button(const std::string& t, const sf::Vector2f& pos, const sf::Color& color, const int& size, const sf::Vector2f& shapePos)
{	
	text.setString(t);
	text.setCharacterSize(24); 
	text.setFillColor(color);

	shape.setFillColor(sf::Color::Blue);
	shape.setSize(sf::Vector2f(50.0f, 50.0f));
	shape.setPosition(shapePos); 
}

sf::Text& Button::getText()
{
	return this->text; 
}

sf::RectangleShape& Button::getShape()
{
	return shape; 
}

void Button::setPosition(sf::Vector2f& pos)
{
	text.setPosition(pos); 
}

void Button::setString(const std::string& t)
{
	text.setString(t);
}

void Button::setFont(const sf::Font& font)
{
	text.setFont(font);
}

void Button::render(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(text);
}

bool Button::mouseClick(sf::RenderWindow& window)
{
	float x = sf::Mouse::getPosition(window).x; 
	float y = sf::Mouse::getPosition(window).y; 

	float shapePosX = shape.getPosition().x;
	float shapePosY = shape.getPosition().y; 

	float width = shapePosX + shape.getLocalBounds().width;
	float height = shapePosY + shape.getLocalBounds().height;


	if (x < width && x > shapePosX && y < height && y > shapePosY)
	{
		text.setFillColor(sf::Color::Red);
		return 1;
	}
	text.setFillColor(sf::Color::Black);
	return 0;
}