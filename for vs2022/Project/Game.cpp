#include "Game.h"

void Game::initVariables()
{
	trafficLane = new TrafficLane; 
	player = new Player; 
	isRunning = false; 
	
	level = 1;
	pause = false; 
	win = false;

	unexpectedExit = false;
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
			unexpectedExit = true; 
			break; 
		case sf::Event::KeyPressed: 
			if (event.key.code == sf::Keyboard::Escape)
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

void Game::renderLevel(sf::RenderWindow& window)
{
	sf::Text text; sf::Font font; font.loadFromFile("Sugar Snow.ttf");
	text.setFont(font);
	std::string curLevel = "LEVEL: " + std::to_string(this->getLevel());
	text.setString(curLevel);
	text.setFillColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(10.0f, 550.0f));
	window.draw(text);
}


void Game::render(sf::RenderWindow& window)
{
	window.clear(); 

	player->render(window); 
	trafficLane->render(window); 
	renderLevel(window);
	window.display();
}

int Game::runGame(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		if (unexpectedExit) return 101;
		if (!win)
			update(window); 
		render(window);

		if (isWin())
		{
			window.clear(sf::Color::Black); // RECHECK
			if (level < 5)
			{
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
			else
			{
				drawWin(window);
				return 20;
			}
			
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

void Game::drawWin(sf::RenderWindow& window)
{
	
	sf::Texture texture; texture.loadFromFile("pic/win.png");
	sf::Sprite sprite; sprite.setTexture(texture); sprite.setPosition(sf::Vector2f(500.0f, 150.0f));
	sf::Text text; sf::Font font; font.loadFromFile("Sugar Snow.ttf");
	text.setFont(font);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Red);
	text.setString("CONGRATULATIONS! YOU HAVE GUIDED THE SANTA THROUGH ALL LEVELS!");
	text.setPosition(sf::Vector2f(25.0f, 500.0f));
	
	sf::Text text2;
	text2.setFont(font);
	text2.setCharacterSize(40);
	text2.setFillColor(sf::Color::Red);
	text2.setString("Press ENTER to proceed");
	text2.setPosition(sf::Vector2f(400.0f, 550.0f));


	while (window.isOpen() && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) == false)
	{
		window.clear(sf::Color(252, 223, 225, 255));
		snowfall.update(window);


		window.draw(sprite);
		window.draw(text);
		window.draw(text2);
		snowfall.render(window);
		window.display();
	}
}

void Game::drawNextLevel(sf::RenderWindow& window)
{
	sf::Text text;
	sf::Font font; 
	sf::Texture texture; texture.loadFromFile("pic/background.png"); 
	sf::Sprite sprite; sprite.setTexture(texture);
	font.loadFromFile("Sugar Snow.TTF"); 
	text.setFont(font); 
	text.setString("NEXT LEVEL : " + std::to_string(level)); 
	text.setFillColor(sf::Color::Red); 
	text.setCharacterSize(40); 
	text.setPosition(300, 300); 
	text.setStyle(sf::Text::Bold); 

	window.draw(sprite);
	window.draw(text);
	window.display(); 
}
