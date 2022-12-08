
#ifndef CROSSING_BUTTON_H
#define CROSSING_BUTTON_H
#include "Header.h"
#include "Game.h"
void menu(sf::RenderWindow &window, sf::Event &Event, sf::Text &startText, sf::Text &loadText, sf::Text &settingsText, int &current);
void setupText(sf::Text &text, std::string str, sf::Font &font, int size, int x, int y);
void setupLevel(sf::RenderWindow &window, sf::Font &font, sf::Event &Event);
#endif //CROSSING_BUTTON_H
