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

	bgMusic = true;
	sound.openFromFile("sound/welcome.ogg");
	//sound.setPlayingOffset(sf::seconds(15.f));
	sound.setVolume(10);
	sound.setLoop(true);
	play_sound();
}

Menu::~Menu() {
	delete window;
	delete event;
	delete game;
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

void Menu::play_sound()
{
	if (bgMusic)
		sound.play();
	else sound.pause();
}

void Menu::renderBackground(sf::RenderWindow& window) // redundant
{
	window.draw(bgSprite);
}

std::string Menu::set_sound()
{
	sf::sleep(sf::seconds(0.175));
	bgMusic = !bgMusic;
	play_sound();
	if (bgMusic)
	{
		std::cout << "Turning sound on!\n";
		return "Music: ON";
	}
	std::cout << "Turning sound off!\n";
	return "Music: OFF";
}

int Menu::renderMain()
{
	std::cout << "renderMain\n" << '\n';
	window->clear();

	std::string menu[5] = { "NEW GAME", "LOAD GAME","RANKING", "MUSIC: ON" , "EXIT" };
	if (!bgMusic) menu[3] = "MUSIC: OFF";
	sf::Font font; font.loadFromFile("Sugar Snow.TTF");
	std::vector <Button> button;

	for (int i = 0; i < 5; i++)
	{
		Button a(menu[i], sf::Vector2f((float)600, (float)(250 + i * 50)), sf::Color::White, 24, sf::Vector2f((float)600, (float)(250 + i * 50)));
		a.setFont(font);
		a.setPosition(sf::Vector2f((float)600, (float)(250 + i * 50)));
		button.push_back(a);
	}

	std::cout << "size: " << button.size() << std::endl;
	sf::Clock clock;
	sf::Time time = sf::seconds(0.10f);
	clock.restart().asSeconds();

	while (window->isOpen())
	{
		pollEvents();

		//renderBackground(*window);
		window->draw(bgSprite);
		for (int i = 0; i < 5; i++) {
			//getShape
			button[i].render(*window);
		}
		for (int i = 0; i < 5; i++)
		{
			button[i].mouseClick(*window);
		}

		if (clock.getElapsedTime() >= time)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (int i = 0; i < 5; i++) {
					if (button[i].mouseClick(*window))
					{
						if (i == 3)
							button[i].setString(set_sound());
						else
							return i;
					}
				}
			}
			clock.restart().asSeconds();
		}

		window->display();
		//window->clear();
	}
	return 4; // RECHECK
}

int Menu::newGame(const int& level)
{
	std::cout << "newGame\n";
	game->setLevel(level);

	int t = game->runGame(*window), lvl = game->getLevel();
	delete game;
	game = new Game;
	window->clear(sf::Color::Black); // RECHECK 

	sf::Texture texture; texture.loadFromFile("pic/background.png");
	sf::Sprite sprite; sprite.setTexture(texture);
	window->draw(sprite);
	window->display();

	if (t == 0)
	{
		int k = subMenu(lvl);
		if (k == 0)
			return newGame(lvl);
		else if (k == 1)
			return newGame(saveGame(lvl));
		else if (k == 2)
			return newGame(loadGame());
		else if (k == 4)
		{
			switch (renderMain())
			{
			case 0:
				return newGame();
				break;
			case 1:
				return loadGame();
				break;
			case 2:
				return rank(); //rank
				break;
			case 3:
				return exitGame();
				break;
			default:
				break;
			}
		}
	}
	else if (t == -1)
	{
		int k = loseMenu();
		if (k == 0)
			return newGame();
		else if (k == 1)
		{
			switch (renderMain())
			{
			case 0:
				return newGame();
				break;
			case 1:
				return loadGame();
				break;
			case 2:
				return rank(); //rank
				break;
			case 3:
				return exitGame();
				break;
			default:
				break;
			}
		}
	}
	else if (t == 2)
		return newGame(lvl); 
}

int Menu::saveGame(const int& Level)
{
	std::cout << "saveGame\n";
	window->clear();

	sf::Texture texture;
	texture.loadFromFile("pic/background.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);


	std::string name = "";
	sf::String sentence;
	sf::Font font; font.loadFromFile("Sugar Snow.TTF");
	sf::Text text(sentence, font, 40); text.setFillColor(sf::Color::Black); text.setPosition(sf::Vector2f(150, 150));

	Button instruction("ENTER YOUR NAME: ", sf::Vector2f(350, 50), sf::Color::Red, 40, sf::Vector2f(350, 50));
	instruction.setFont(font);
	instruction.setPosition(sf::Vector2f(350, 50));
	Button textBox("     ", sf::Vector2f(125, 140), sf::Color::Red, 40, sf::Vector2f(125, 140));
	textBox.setFont(font);
	textBox.setPosition(sf::Vector2f(125, 140));
	Button enter("SAVE", sf::Vector2f(840, 140), sf::Color::Red, 40, sf::Vector2f(840, 140));
	enter.setFont(font);
	enter.setPosition(sf::Vector2f(840, 140));


	while (window->isOpen() && name.length() == 0)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (enter.mouseClick(*window))
				{
					name = sentence.toAnsiString();
					break;
				}
			}
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode >= 32 && event.text.unicode <= 126)
					sentence += (char)event.text.unicode;
				else if (event.text.unicode == 8 && sentence.getSize() > 0) // backspace
					sentence.erase(sentence.getSize() - 1);
				text.setString(sentence);
			}
		}

		window->draw(sprite);
		instruction.render(*window);
		textBox.render(*window);
		enter.render(*window);

		enter.mouseClick(*window);
		window->draw(text);
		window->display();
		window->clear();
	}


	std::ofstream fout;
	std::ifstream fin;

	fin.open("loadGame.txt", std::ios::in);
	if (!fin.is_open())
		std::cout << "Couldn't open load file" << std::endl;
	else
	{
		std::vector<std::pair<std::string, int>> list;
		int level;
		std::string info;
		std::string acc;
		std::string lvl;
		bool check = false;

		while (fin >> info)
		{
			for (int i = 0; i < info.length(); i++)
			{
				if (info[i] != ',')
					acc += info[i];
				else
				{
					while (i + 1 < info.length())
						lvl += info[++i];
					level = stoi(lvl);
					break;
				}
			}

			if (acc == name) {
				check = true;
				level = Level;
			}

			list.push_back(make_pair(acc, level));

			acc.clear();
			lvl.clear();
			info.clear();
		}
		fin.close();

		if (check)
			fout.open("loadGame.txt");
		else
			fout.open("loadGame.txt", std::ios::app);

		if (!fout.is_open())
		{
			std::cout << "Could not open load file\n";
		}
		else
		{
			if (check)
			{
				/*for (int i = 0; i < list.size(); i++)
				{
					fout << list[i].first << ',' << list[i].second << '\n';
				}*/

				for (auto i = list.begin(); i != list.end(); i++)
					fout << i->first << ',' << i->second << '\n';
			}
			else
				fout << name << ',' << Level << '\n';
			fout.close();
		}

		std::cout << "Save successfully\n";
		return Level;
	}
	return 1;
}

int Menu::loadLevel(const sf::String& name)
{
	std::ifstream fin;
	std::ofstream fout;
	std::string account;
	std::string info;
	std::string lvl;
	int level = 1;

	fin.open("loadGame.txt");
	if (!fin.is_open())
	{
		std::cout << "Couldn't open file\n";
		//RECHECK : draw error background
	}
	else
	{
		while (fin >> info)
		{
			for (int i = 0; i < info.length(); i++)
			{
				if (info[i] != ',')
					account += info[i];
				else if (info[i] == ',' && account == name)
				{
					while (i + 1 < info.length())
						lvl += info[++i];
					level = stoi(lvl);
					fin.close();
					std::cout << "Loaded account " << "\ " << account << "\ " << "successfully. \n";
					return level;
				}
			}
			account.clear();
		}
		fin.close();
	}

	fout.open("loadGame.txt", std::ios::app);
	fout << "autosave," << 1 << std::endl;
	fout.close();
	
	//display 
	window->clear();
	sf::Texture texture; texture.loadFromFile("pic/background.png");
	sf::Sprite sprite; sprite.setTexture(texture);
	window->draw(sprite);

	sf::Texture texture1; texture1.loadFromFile("pic/stupid.png"); 
	sf::Sprite sprite1; sprite1.setTexture(texture1);
	sprite1.setScale(sf::Vector2f(0.5f, 0.5f)); 
	sprite1.setPosition(sf::Vector2f(500.0f, 100.0f)); 
	window->draw(sprite1); 

	std::string txt[2] = { "Load accout does not exist ", "Loading autosave account"}; 
	sf::Font font; font.loadFromFile("Sugar Snow.ttf");
	sf::Text text[2];
	for (int i = 0; i < 2; i++)
	{
		text[i].setFont(font);
		text[i].setFillColor(sf::Color::Black);
		text[i].setString(txt[i]);
		text[i].setCharacterSize(50);
		text[i].setPosition(sf::Vector2f(300.0f, 300.0f + (i+1)*100));
		window->draw(text[i]);
		
	}
	window->display();
	sf::sleep(sf::seconds(3.0f)); 


	std::cout << "Load accout does not exist | Loading autosave account\n";

	return level;
}

int Menu::subMenu(const int& clevel)
{
	window->clear();
	std::cout << "subMenu\n";
	//RECHECK: load background 


	/*0 : resume
	1 : save game
	2 : music
	3 : exit */
	std::string menu[5] = { "RESUME", "SAVE GAME", "LOAD GAME", "MUSIC: ON", "EXIT" }; // RECHECK :  add music -> resize = 4

	// RECHECK: add music : menu[2] = music (on/off) 
	sf::Font font; font.loadFromFile("Sugar Snow.TTF");
	std::vector <Button> menuButton;
	sf::Texture texture;
	sf::Sprite sprite;
	texture.loadFromFile("pic/background.png");
	sprite.setTexture(texture);
	//sprite.setPosition(sf::Vector2f(300, 300));
	std::string curLevel = "CURRENT LEVEL: " + std::to_string(clevel);


	Button level(curLevel, sf::Vector2f(200, 200), sf::Color::Red, 40, sf::Vector2f(200, 200)); //RECHECK 
	level.setFont(font);
	level.setPosition(sf::Vector2f(200, 200));

	sf::Clock clock;
	sf::Time time = sf::seconds(0.10f);
	clock.restart().asSeconds();

	for (int i = 0; i < 5; i++) // RECHECK : add music -> i < 4
	{
		sf::Vector2f pos(window->getSize().x / 2 + 110, i * 65 + 220);
		Button a(menu[i], pos, sf::Color::Red, 40, pos);
		a.setFont(font);
		a.setPosition(pos);
		menuButton.push_back(a);
	}

	while (window->isOpen())
	{
		pollEvents();
		window->draw(sprite);
		for (int i = 0; i < 5; i++)
		{
			menuButton[i].render(*window);
		}
		level.render(*window);
		window->display();

		if (clock.getElapsedTime() >= time)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (int i = 0; i < 5; i++)
				{
					if (menuButton[i].mouseClick(*window))
					{
						if (i == 3)
							menuButton[i].setString(set_sound());
						else
							return i;
					}
				}
			}
		}

		for (int i = 0; i < 5; i++)
			menuButton[i].mouseClick(*window);
		window->clear();
	}
	return 1;
}

int Menu::loseMenu()
{
	std::cout << "loseMenu\n";
	window->clear();
	std::string menu[2] = { "TRY AGAIN", "QUIT" };
	sf::Text crash;
	std::vector <Button> menuButton;
	sf::Font font;
	font.loadFromFile("Sugar Snow.TTF");

	crash.setPosition(sf::Vector2f(140, 190));
	crash.setFont(font);
	crash.setString("CRASHED");
	crash.setCharacterSize(165);
	crash.setFillColor(sf::Color::Red);

	for (int i = 0; i < 2; i++)
	{
		sf::Vector2f pos(window->getSize().x / 2 + 160, i * 65 + 250);
		Button a(menu[i], pos, sf::Color::Black, 24, pos);
		a.setFont(font);
		a.setPosition(pos);
		menuButton.push_back(a);
	}
	window->clear(); 

	sf::Texture texture; texture.loadFromFile("pic/background.png"); 
	sf::Sprite sprite; sprite.setTexture(texture); 
	window->draw(sprite);

	while (window->isOpen())
	{
		pollEvents();
		for (int i = 0; i < 2; i++)
		{
			menuButton[i].render(*window);
		}
		window->draw(crash);
		window->display();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (int i = 0; i < 2; i++)
			{
				if (menuButton[i].mouseClick(*window))
					return i;
			}
		}

		for (int i = 0; i < 2; i++)
			menuButton[i].mouseClick(*window);
	}
	return 1;
}

int Menu::loadGame()
{
	std::cout << "loadGame\n";
	window->clear();

	sf::Texture texture;
	texture.loadFromFile("pic/background.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);

	std::string name = "";
	sf::String sentence;
	sf::Font font; font.loadFromFile("Sugar Snow.TTF");
	sf::Text text(sentence, font, 40); text.setFillColor(sf::Color::Black); 
	text.setPosition(sf::Vector2f(350, 140)); 

	Button instruction("ENTER YOUR NAME: ", sf::Vector2f(350, 50), sf::Color::Red, 40, sf::Vector2f(350, 50));
	instruction.setFont(font);
	instruction.setPosition(sf::Vector2f(350, 50));
	Button textBox("     ", sf::Vector2f(125, 140), sf::Color::Red, 40, sf::Vector2f(125, 140));
	textBox.setFont(font);
	textBox.setPosition(sf::Vector2f(125, 140));
	Button enter("LOAD", sf::Vector2f(840, 140), sf::Color::Red, 40, sf::Vector2f(840, 140));
	enter.setFont(font);
	enter.setPosition(sf::Vector2f(840, 140));


	while (window->isOpen() && name.length() == 0)
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (enter.mouseClick(*window))
				{
					name = sentence.toAnsiString();
					break;
				}
			}
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode >= 32 && event.text.unicode <= 126)
					sentence += (char)event.text.unicode;
				else if (event.text.unicode == 8 && sentence.getSize() > 0)
					sentence.erase(sentence.getSize() - 1);
				text.setString(sentence);
			}

			window->draw(sprite);
			instruction.render(*window);
			textBox.render(*window);
			enter.render(*window);


			enter.mouseClick(*window);

			window->draw(text);
			window->display();
			window->clear();
		}
	}
	return newGame(loadLevel(name));
}

int Menu::exitGame()
{
	std::cout << "exitGame\n";

	bgMusic = !bgMusic; 
	play_sound(); 
	window->clear();
	sf::Texture texture; texture.loadFromFile("pic/bye.png"); 
	sf::Sprite sprite; sprite.setTexture(texture); 
	window->draw(sprite); 

	sf::Text text; sf::Font font; font.loadFromFile("Sugar Snow.ttf"); 
	text.setString("GOOD BYE"); text.setFillColor(sf::Color::Black); text.setFont(font); 
	text.setPosition(sf::Vector2f(550.0f, 600.0f)); text.setCharacterSize(50); 
	window->draw(text); 
	window->display(); 

	sf::Music m;
	m.openFromFile("sound/merry-christmas.ogg"); 
	m.setVolume(100);
	m.setLoop(0);
	m.play(); 
	sf::sleep(sf::seconds(4.0f));


	window->close();
	this->~Menu();
	exit(0);
	return 0;
}

int Menu::instruction()
{
	window->clear();
	sf::Texture texture;
	texture.loadFromFile("pic/shiba.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sf::Event event;
	while (window->isOpen())
	{
		pollEvents();
		window->draw(sprite);
		window->display();
	}
	return 2;
}

int Menu::rank()
{
	std::cout << "rank\n"; 
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) == false && window->isOpen())
	{
		window->clear();
		std::vector<std::string> info;
		std::vector<int> level;
		std::vector<std::pair<Button, Button>> box;
		std::vector<Button> num;
		sf::Texture texture; texture.loadFromFile("pic/background.png");
		sf::Sprite sprite; sprite.setTexture(texture);
		window->draw(sprite);
		Button title("TOP 5 BEST PLAYERS:", sf::Vector2f(200.0f, 30.0f), sf::Color::Black, 40, sf::Vector2f(300.0f, 300.0f));
		sf::Text esc;
		sf::Font font; font.loadFromFile("Sugar Snow.TTF");
		esc.setString("Press Enter to return to Menu");
		esc.setFont(font);
		esc.setFillColor(sf::Color::Black);
		esc.setCharacterSize(40);
		esc.setPosition(sf::Vector2f(300.0f, 600.0f));
		
		title.setFont(font);
		title.setPosition(sf::Vector2f(350.0f, 50.0f));
		title.render(*window);

		window->draw(esc);


		std::ifstream fin;
		fin.open("loadGame.txt", std::ios::in);

		if (!fin.is_open())
		{
			std::cout << "Can't open file\n"; 
			window->close(); //RECHECK 
		}
		else
		{
			std::cout << "can open file\n"; 
			std::string infoLine;
			std::string acc;
			std::string levelStr;
			int l;
			while (fin >> infoLine)
			{
				std::cout << "infoLine.length(): " << infoLine.length() << '\n';
				for (int i = 0; i < infoLine.length(); i++)
				{
					if (infoLine[i] != ',')
						acc += infoLine[i];
					else
					{
						while (i + 1 < infoLine.length())
							levelStr += infoLine[++i];

						l = stoi(levelStr);
						break;
					}
				}

				level.push_back(l);
				info.push_back(acc);

				acc.clear();
				infoLine.clear();
				levelStr.clear();
			}
			fin.close();
		}
		std::cout << "sort\n";
		//sort
		if (level.size())
		{
			for (int i = 0; i < level.size() - 1; i++)
			{
				for (int j = i + 1; j < level.size(); j++)
				{
					if (level.at(j) > level.at(i))
					{
						swap(level.at(i), level.at(j));
						swap(info.at(i), info.at(j));
					}
				}
			}
		}
		std::cout << "display\n"; 
		//display
		for (int i = 0; i < level.size(); i++)
		{
			if (i < 5)
			{
				Button context(info[i], sf::Vector2f(200, 250), sf::Color::Black, 40, sf::Vector2f(200, 250));
				Button lvl(std::to_string(level[i]), sf::Vector2f(200, 350), sf::Color::Black, 40, sf::Vector2f(200, 350));
				Button n(std::to_string(i + 1), sf::Vector2f(200, 450), sf::Color::Black, 40, sf::Vector2f(200, 450));

				context.setFont(font);
				lvl.setFont(font);
				n.setFont(font);

				context.setPosition(sf::Vector2f(250, 50 +(i+1)*100));
				lvl.setPosition(sf::Vector2f(700, 50 + (i + 1) * 100));
				n.setPosition(sf::Vector2f(200, 50 + (i + 1) * 100));

				box.push_back(std::make_pair(context, lvl));
				num.push_back(n);
			}
			else break;
		}
		std::cout << "Box size: " << box.size() << std::endl; 
		
		for (int i = 0; i < box.size(); i++)
		{
			box[i].first.render(*window);
			box[i].second.render(*window);
			num[i].render(*window);
		}
		window->display();
	}

	switch (renderMain())
	{
	case 0:
		return newGame();
		break;
	case 1:
		return loadGame();
		break;
	case 2:
		return rank();
		break;
	case 3:
		return exitGame();
		break;
	default:
		break;
	}
}

template <class T>
inline void Menu::swap(T& a, T& b)
{
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}


