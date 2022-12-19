#include "Button.h"

Button::Button() {}

Button::~Button() {}

Button::Button(const std::string& t, const sf::Vector2f& pos, const sf::Color& color, const int& size)
{
	font.loadFromFile("ARCADECLASSIC.TTF");
	text.setFont(font); 
	text.setPosition(pos); 
	text.setFillColor(color);
	text.setString(t);
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(text);
}

bool Button::mouseClick(sf::RenderWindow& window)
{
	float x = sf::Mouse::getPosition(window).x; 
	float y = sf::Mouse::getPosition(window).y; 

	sf::Vector2f mousePos(x, y); 
	if (text.getGlobalBounds().contains(mousePos)) {
		text.setFillColor(sf::Color::Red); 
		return 1; 
	}
	else return 0; 
}