#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

void renderSprite(sf::RenderTarget& target, const sf::Sprite& sprite)
{
	target.draw(sprite); 
}

void renderText(sf::RenderTarget& target, const sf::Text& text)
{
	target.draw(text); 
}

void renderShape(sf::RenderTarget& target, const sf::Shape& shape)
{
	target.draw(shape);
}