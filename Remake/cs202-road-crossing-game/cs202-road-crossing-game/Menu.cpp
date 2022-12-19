#include "Menu.h"
#include "Button.h"

void Menu::initVariables()
{
	event = new sf::Event; 
	game = new Game; 
}

void Menu::initWindow()
{
	videoMode.width = 1280; 
	videoMode.height = 720; 
	window = new sf::RenderWindow(videoMode, "Crossing Road", sf::Style::Close | sf::Style::Titlebar); 
	window->setFramerateLimit(60);
}

void Menu::initBackground()
{
	bgTexture.loadFromFile("pic/background.png"); 
	bgSprite.setTexture(bgTexture); 
}

Menu::Menu()
{
	initVariables();
	initWindow();
	initBackground();
}

Menu::~Menu() {}

const bool Menu::isRunning() const
{
	return window->isOpen();
}

void Menu::pollEvents()
{
	while (window->pollEvent(*event))
	{
		switch (event->type)
		{
			case sf::Event::Closed: 
				window->close(); 
				break; 
			case sf::Event::KeyPressed: 
				if (event->key.code == sf::Keyboard::Escape)
					window->close(); 
				break; 
			default:
				break;
		}
	}
}

int Menu::renderMain()
{
	window->clear(); 

	std::string menu[4] = { "NEW GAME", "LOAD GAME", "INSTRUCTIONS" , "EXIT" }; 
	std::vector <Button> button; 
	for (int i = 0; i < 4; i++)
	{
		Button a(menu[i], { 200, 300 + i * 50 }, sf::Color::Black, 24); 
		button.push_back(a); 
	}
	sf::Clock clock; 
	sf::Time time = sf::seconds(0.10f); 
	clock.restart().asSeconds(); 

	while (window->isOpen())
	{
		pollEvents(); 
		for (int i = 0; i < 4; i++) button[i].render(*window);

		if (clock.getElapsedTime() >= time)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (int i = 0; i < 5; i++) {
					if (button[i].mouseClick(*window))
					{
						return i; 
					}
				}
			}
			clock.restart().asSeconds();
		}
		renderSprite(*window, bgSprite);
		window->display();
	}
	return 4; // RECHECK
}

int Menu::newGame(const int& level)
{
	game->setLevel(level); 

	int t = game->runGame(*window), lvl = game->getLevel(); 
	delete game; 
	game = new Game; 
	window->clear(sf::Color::Black); // RECHECK 
	window->display(); 

	if (t == 0)
	{
		int k = subMenu(lvl); 
	}
}

int Menu::saveGame(const int& level)
{
	return 0;
}

int Menu::loadLevel(const sf::String& name)
{
	return 0;
}

int Menu::subMenu(const int& level)
{
	window->clear();
	// RECHECK: load background

	/*0: resume
	1: save game
	2: music
	3: exit*/
	std::string menu[3] = { "RESUME" , "SAVE GAME", "EXIT" }; //RECHECK" add music -> resize : 4 
	
	sf::Text text[2]; 
	std::vector<Button> menuButton; 
	sf::Font font; 

}
