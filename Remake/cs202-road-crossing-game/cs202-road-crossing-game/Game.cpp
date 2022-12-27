#include "Game.h"

void Game::initVariables()
{
	trafficLane = new TrafficLane; 
	player = new Player; 
	isRunning = false; 
	
	level = 1;
	pause = false; 
	win = false;
}

Game::Game()
{
	level = 1; 
	initVariables();
}

Game::~Game()
{
	delete trafficLane; 
	delete player; 
}

void Game::pollEvents(sf::RenderWindow& window)
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed: 
			window.close(); 
			break; 
		case sf::Event::KeyPressed: 
			if (event.key.code == sf::Keyboard::Escape)
				window.close(); 
			if (event.key.code == sf::Keyboard::P)
				pause = true; 
			break; 
		default:
			break;
		}
	}
}

void Game::update(sf::RenderWindow& window)
{
	pollEvents(window); 
	player->update(window);
	trafficLane->update(window, level); 
}

void Game::render(sf::RenderWindow& window)
{
	window.clear(); 

	player->render(window); 
	trafficLane->render(window); 

	window.display();
}

int Game::runGame(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		if (!win)
			update(window); 
		render(window);

		if (isWin())
		{
			window.clear(sf::Color::Black); // RECHECK
			drawNextLevel(window); 
			sf::Clock clock; 
			int t = 3; 
			clock.restart().asSeconds(); 
			while (true) {
				if (clock.getElapsedTime().asSeconds() > t) {
					win = false; 
					break; 
				}
			}
			//window.clear(sf::Color::Black); // RECHECK 
			player->reset(); 
			return runGame(window); 
		}

		// Pause Game
		else if (pause)
		{
			return 0; 
		}
		
		//Lose Game
		else if (trafficLane->Collision(player->getshape().getGlobalBounds()))
		{
			return -1; 
		}

	}
	return 10;
}

void Game::setLevel(const int& level)
{
	this->level = level; 
}

int Game::getLevel()
{
	return level; 
}

bool Game::isWin()
{
	if (player->getshape().getGlobalBounds().top == 0)
	{
		++level;
		win = true; 
		return true; 
	}
	return false;
}

void Game::drawNextLevel(sf::RenderWindow& window)
{
	sf::Text text;
	sf::Font font; 
	font.loadFromFile("Sugar Snow.TTF"); 
	text.setFont(font); 
	text.setString("NEXT LEVEL : " + std::to_string(level)); 
	text.setFillColor(sf::Color::Red); 
	text.setCharacterSize(40); 
	text.setPosition(300, 300); 
	text.setStyle(sf::Text::Bold); 

	window.draw(text);
	window.display(); 
}
