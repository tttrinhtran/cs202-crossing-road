#pragma once
#include "Header.h"

class Button
{
private: 
	sf::Font font;
	sf::Text text;  
	sf::RectangleShape shape; 
public: 
	Button();
	~Button(); 

	Button(const std::string& t, const sf::Vector2f& pos, const sf::Color& color, const int& size, const sf::Vector2f& shapePos); 

	sf::Text& getText();
	sf::RectangleShape& getShape();
	void setPosition(sf::Vector2f& pos);
	void setString(const std::string& t); 
	void setFont(const sf::Font& font); 
	void render(sf::RenderWindow& window);
	bool mouseClick(sf::RenderWindow& window); 
};

