#pragma once
#include "Header.h"
#include "Game.h"

//0 : new game
//1 : load game
//2 : instruction 
//3 : exit

class Menu
{
private: 
	sf::RenderWindow* window; 
	sf::VideoMode videoMode; 
	sf::Event* event;
	sf::Texture bgTexture; 
	sf::Sprite bgSprite; 
	//sf::Music sound; 

	Game* game = nullptr; 

	void initVariables(); 
	void initWindow(); 
	void initBackground(); 
public: 
	Menu(); 
	virtual ~Menu(); 

	const bool isRunning() const; 
	void pollEvents(); 

	//Menu list of choice
	int renderMain();
	int newGame(const int& level = 1); 
	int saveGame(const int& level); 
	int loadLevel(const sf::String& name); 
	int subMenu(const int& level);
};

