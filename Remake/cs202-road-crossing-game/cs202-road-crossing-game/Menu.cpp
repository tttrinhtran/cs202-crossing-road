#include "Menu.h"

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
		window->display();
	}
	return 4; //	RE-CHECK
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
		int k = drawSubMenu(lvl); 
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

Button::Button() {}

Button::~Button() {}

Button::Button(const std::string& t, const sf::Vector2f& pos, const sf::Color& color, const int& size)
{
	font.loadFromFile("ARCADECLASSIC.TTF");
	text.setFont(font); 
	text.setPosition(pos); 
	text.setFillColor(color);
	text.setString(t);
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(text);
}

bool Button::mouseClick(sf::RenderWindow& window)
{
	float x = sf::Mouse::getPosition(window).x; 
	float y = sf::Mouse::getPosition(window).y; 

	sf::Vector2f mousePos(x, y); 
	if (text.getGlobalBounds().contains(mousePos)) {
		text.setFillColor(sf::Color::Red); 
		return 1; 
	}
	else return 0; 
}
