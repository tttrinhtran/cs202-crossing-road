#include "Game.h"
#include "Obstacle.h"
void Game::initFont()
{
	if (!font.loadFromFile("ARCADECLASSIC.TTF"))
	{
		std::cout << "Load font failed\n"; 
	}
}

void Game::initText()
{
	text.setFont(font); 
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(32); 
	text.setString("HELLO WORLD"); 
	text.setPosition(300, 300); 
}

void Game::initWindow()
{
	videoMode.height = 600; videoMode.width = 1000; 
	window = new sf::RenderWindow(videoMode, "Crossing Road", sf::Style::Close | sf::Style::Titlebar); 
	window->setFramerateLimit(60); 
}

void Game::initVariables()
{
	endGame = false; 
	maxObs = 15; 
	curPos.x = 0.f; curPos.y = 0.f; 
}

void Game::initBackground()
{
	bgTexture.loadFromFile("pic/background.png"); 
	bgSprite.setTexture(bgTexture); 
}

Game::Game()
{
	initVariables(); 
	initWindow(); 
	initFont(); 
	initText(); 
	initBackground();
	initAnimation();
}

Game::~Game()
{
	delete window; 
}

const bool Game::isRunning() const
{
	return window->isOpen(); 
}

const bool& Game::getEndGame() const
{
	return endGame; 
}

void Game::pollEvents()
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed: 
				window->close(); 
				break; 
			case sf::Event::KeyPressed: 
				if (event.key.code == sf::Keyboard::Escape)
					window->close(); 
				break; 
			default:
				break;
		}
	}
}

void Game::initAnimation()
{
	animationTimer.restart();
}

void Game::spawnObstacle()
{
	//if (animationTimer.getElapsedTime().asSeconds() >= 0.5f)
	//{
	//	Obstacle o(curPos, *window);
	//	obs.push_back(o);
	//	curPos = obs.back().getSprite().getPosition();
	//	std::cout << curPos.x << '\n' << "size: " << obs.size() << '\n';

	//	/*if (this->obs.size() < maxObs)
	//	{
	//		
	//	}*/
	//	animationTimer.restart();
	//}

	if (animationTimer.getElapsedTime().asSeconds() >= 0.5f)
	{
		for (auto& i : tmp)
		{
			i.setPosition();
		}
		
		Temp t(*window, curPos);
		tmp.push_back(t);
		animationTimer.restart();
	}
}

void Game::removeObstacle()
{
	//for (int i = 0; i < obs.size(); i++)
	//{
	//	if (obs[i].getSprite().getGlobalBounds().left + obs[i].getSprite().getGlobalBounds().width >= window->getSize().x)
	//	{
	//		// remove obstacle
	//		obs.erase(obs.begin() + i);
	//	}
	//}
}

void Game::updateAnimation()
{
	//if (animationTimer.getElapsedTime().asSeconds() >= 0.2f)
	//{
	//	//spawnObstacle(); 
	//	removeObstacle();
	//	animationTimer.restart();
	//}

	for (int i = 0; i < tmp.size(); i++)
	{
		if (tmp[i].getShape().getGlobalBounds().left + tmp[i].getShape().getGlobalBounds().width >= window->getSize().x)
		{
			tmp.erase(tmp.begin() + i);
		}
	}
}

void Game::updatePlayer()
{
	player.update(*window);
	
	if (player.getHP() <= 0)
		endGame = true; 
}

void Game::update()
{
	pollEvents();
	if (endGame == false)
	{
		spawnObstacle();
		player.update(*window);
		updateAnimation();
		//removeObstacle();
	}
}

void Game::renderBackground(sf::RenderTarget& target)
{
	target.draw(bgSprite);
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(text);
}

void Game::render()
{
	window->clear(); 

	renderBackground(*window);
	renderText(*window);
	
	player.render(*window);

	/*for (auto& i : tmp)
	{
		i.render(window);
	}*/
	for (int i = tmp.size() - 1; i >= 0; i--)
	{
		tmp[i].render(window);
	}

	window->display(); 
}
