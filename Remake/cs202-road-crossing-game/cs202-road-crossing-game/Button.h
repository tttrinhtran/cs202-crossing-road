#pragma once
#include "Header.h"

class Button
{
private: 
	sf::Font font;
	sf::Text text;  
public: 
	Button();
	virtual ~Button(); 

	Button(const std::string& t, const sf::Vector2f& pos, const sf::Color& color, const int& size); 
	
	void render(sf::RenderTarget& target);
	bool mouseClick(sf::RenderWindow& window); 
};

