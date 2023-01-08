#pragma once
#include "Header.h"
#include "Game.h"
#include "Snowfall.h"

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
	sf::Music sound; 
	bool bgMusic; 

	Game* game = nullptr; 
	Snowfall snowfall;

	void initVariables(); 
	void initWindow(); 
	void initBackground(); 
public: 
	Menu();
	virtual ~Menu();

	int show();
	void pollEvents();
	void play_sound();
	std::string set_sound();
	void renderBackground(sf::RenderWindow& window);
	//Menu list of choice
	int renderMain();
	int newGame(const int& level = 1);
	int saveGame(const int& level);
	int loadLevel(const sf::String& name);
	int subMenu(const int& level);
	int loseMenu();
	int loadGame();
	int rank(); 
	template<class T> void swap(T& a, T& b);
	void drawBye(); 
	int exitGame();
	int instruction();
};

// #include "Menu.cpp"