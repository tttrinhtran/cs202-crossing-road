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
	window = new sf::RenderWindow(videoMode, "The Santa's Crossing Road", sf::Style::Close | sf::Style::Titlebar);
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
	sound.setVolume(30);
	sound.setLoop(true);
	play_sound();
}

Menu::~Menu() {
	delete window;
	delete event;
	delete game;
}

bool Menu::pollEvents(sf::Event &event, bool forceReturn)
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				exitGame();
				return false;
			// case sf::Event::KeyPressed:
			// 	if (event->key.code == sf::Keyboard::Escape)
			// 		window->close();
			// 	break;
			default:
				if (forceReturn) return true;
		}
	}

	return false;
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

	std::string menu[6] = { "NEW GAME", "LOAD GAME","RANKING", "MUSIC: ON" , "INSTRUCTION", "EXIT" };
	if (!bgMusic) menu[3] = "MUSIC: OFF";
	sf::Font font; font.loadFromFile("Sugar Snow.TTF");
	std::vector <Button> button;

	for (int i = 0; i < 6; i++)
	{
		Button a(menu[i], sf::Vector2f((float)600, (float)(250 + i * 50)), sf::Color::Black, 24, sf::Vector2f((float)600, (float)(250 + i * 50)));
		a.setFont(font);
		a.setPosition(sf::Vector2f((float)600, (float)(300 + i * 50)));
		button.push_back(a);
	}

	std::cout << "size: " << button.size() << std::endl;
	sf::Clock clock;
	sf::Time time = sf::seconds(0.10f);
	clock.restart().asSeconds();

	//decor
	sf::Texture tt; tt.loadFromFile("pic/snowman.png");
	sf::Sprite sp; sp.setTexture(tt); 
	sp.setPosition(sf::Vector2f(270.0f, 300.0f));
	
	sf::Texture tt1; tt1.loadFromFile("pic/tree.png");
	sf::Sprite sp1; sp1.setTexture(tt1); 
	sp1.setPosition(sf::Vector2f(850.0f, 280.0f));

	std::string txt[2] = { "THE SANTA'S CROSSING ROAD", "MADE BY GROUP 05" }; 
	sf::Text text[2];  
	for (int i = 0; i < 2; i++)
	{
		text[i].setString(txt[i]); 
		text[i].setFont(font); 
		text[i].setPosition(sf::Vector2f(450.0f, (i + 1) * 80)); 
		text[i].setFillColor(sf::Color (4, 68, 43));
		text[i].setCharacterSize(60);
	}

	while (window->isOpen())
	{
		sf::Event event;
		pollEvents(event, false);
		//renderBackground(*window);
		window->draw(bgSprite);
		snowfall.update(*window);
		snowfall.render(*window);
		window->draw(sp);
		window->draw(sp1);
		for (int i = 0; i < 2; i++)
			window->draw(text[i]);
		for (int i = 0; i < 6; i++) {
			//getShape
			button[i].render(*window);
		}
		for (int i = 0; i < 6; i++)
		{
			button[i].mouseClick(*window);
		}

		if (clock.getElapsedTime() >= time)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (int i = 0; i < 6; i++) {
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

	while (t == 0)
	{
		int k = subMenu(lvl);
		switch (k) {
			case 0: return newGame(lvl);
			case 1: saveGame(lvl, "loadGame.txt", "", false); break;
			case 2: return newGame(loadGame());
			case 4: return show();
			default: return 0;
		}
	}
	bool user_saved = false;
	while (t == -1)
	{
		if (!user_saved) {
			if (lvl > 0) saveGame(lvl, "loadRank.txt", "YOU LOSE!", true);
			user_saved = true;
			continue;
		}
		else {
			int k = loseMenu();
			if (k == 0) return newGame(0);
			if (k == 1) return show();
			return 0;
		}
	}
	if (t == 2) return newGame(lvl);
	if (t == 20) {
		saveGame(lvl, "loadRank.txt", "YOU WIN!", true);
		return show();
	}
	if (t == 101) exitGame();
	return 0;
}

int Menu::saveGame(const int& Level, std::string fileName, std::string additionalInfo, bool allowDup)
{
	std::cout << "saveGame\n";
	window->clear();

	sf::Texture texture;
	texture.loadFromFile("pic/background.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	

	std::string name = "";
	sf::String sentence = "";
	sf::Font font; font.loadFromFile("Sugar Snow.TTF");
	sf::Text text(sentence, font, 40); text.setFillColor(sf::Color::Black); text.setPosition(sf::Vector2f(150, 150));

	Button instruction(additionalInfo + " ENTER YOUR NAME: (Press ESC to skip)", sf::Vector2f(350, 50), sf::Color::Red, 40, sf::Vector2f(350, 50));
	instruction.setFont(font);
	instruction.setPosition(sf::Vector2f(350, 50));
	Button textBox("     ", sf::Vector2f(125, 140), sf::Color::Red, 40, sf::Vector2f(125, 140));
	textBox.setFont(font);
	textBox.setPosition(sf::Vector2f(125, 140));
	Button enter("SAVE", sf::Vector2f(840, 140), sf::Color::Red, 40, sf::Vector2f(840, 140));
	enter.setFont(font);
	enter.setPosition(sf::Vector2f(840, 140));

	sf::Event event;
	bool submitted = false;
	while (window->isOpen() && !submitted)
	{
		while (pollEvents(event, true)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (enter.mouseClick(*window))
				{
					name = sentence.toAnsiString();
					if (name.length() > 0) {
						submitted = true;
						break;
					}
				}
			}

			int proc = textField(event, sentence);
			if (proc == 1) {
				name = sentence.toAnsiString();
				if (name.length() > 0) {
					submitted = true;
					break;
				}
			}
			if (proc == -1) return -1;
			if (proc == 2) text.setString(sentence);
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

	std::vector<std::pair<std::string, int>> list;
	bool userExists = false;

	if (!allowDup) {
		std::ifstream fin;
		fin.open(fileName);
		int level;
		std::string info;
		std::string acc;
		std::string lvl;

		while (std::getline(fin, info))
		{
			if (info == "") continue;
			int i = 0;
			for (; i < info.length(); i++)
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
				userExists = true;
				level = Level;
			}
			else if (i == info.length() || level < 0) continue;

			list.push_back(make_pair(acc, level));

			acc.clear();
			lvl.clear();
			info.clear();
		}
		fin.close();
	}

	for (int i = 0; i < name.length(); ++i) {
		if (name[i] == ',') name[i] = '.';
	}

	if (userExists) fout.open(fileName);
	else fout.open(fileName, std::ios::app);

	if (!fout.is_open())
	{
		std::cout << "Could not open write file\n";
	}
	else
	{
		if (userExists) {
			for (auto i : list) fout << i.first << ',' << i.second << '\n';
		}
		else fout << '\n' << name << ',' << Level;
		fout.close();
	}
		
	//decor

	window->clear();
	window->draw(sprite);

	sf::Texture texture1; texture1.loadFromFile("pic/stupid.png");
	sf::Sprite sprite1; sprite1.setTexture(texture1);
	sprite1.setScale(sf::Vector2f(0.5f, 0.5f));
	sprite1.setPosition(sf::Vector2f(500.0f, 100.0f));
	window->draw(sprite1);

	sf::Text text1; 
	text1.setFont(font); text1.setString("SAVING ACCOUNT SUCCESFULLY"); 
	text1.setFillColor(sf::Color::Black); 
	text1.setCharacterSize(50);
	text1.setPosition(sf::Vector2f(300.0f, 400.0f)); 
	window->draw(text1);
	window->display();
	sf::sleep(sf::seconds(3.0f));

	std::cout << "Save successfully\n";
	return Level;
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
		while (std::getline(fin, info))
		{
			if (info == "") continue;
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
					std::cout << "Loaded account: " << account << " | " << "success. \n";
					return level;
				}
			}
			account.clear();
		}
		fin.close();
	}

	fout.open("loadGame.txt", std::ios::app);
	fout << "\nautosave," << 1 << std::endl;
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
	std::string menu[5] = { "RESUME", "SAVE GAME", "LOAD GAME", "MUSIC: ON", "BACK TO MAIN MENU" }; // RECHECK :  add music -> resize = 4

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
	level.setPosition(sf::Vector2f(200, 250));

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
		sf::Event event;
		while (pollEvents(event, true)) {
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) return 0;
		}

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
	std::string menu[2] = { "TRY AGAIN", "BACK TO MENU" };
	sf::Text crash;
	std::vector <Button> menuButton;
	sf::Font font;
	font.loadFromFile("Sugar Snow.TTF");

	crash.setPosition(sf::Vector2f(140, 190));
	crash.setFont(font);
	crash.setString("CRASHED!");
	crash.setCharacterSize(165);
	crash.setFillColor(sf::Color::Red);

	for (int i = 0; i < 2; i++)
	{
		sf::Vector2f pos(window->getSize().x / 2 + 200, i * 65 + 250);
		Button a(menu[i], pos, sf::Color::Black, 24, pos);
		a.setFont(font);
		a.setPosition(pos);
		menuButton.push_back(a);
	}

	while (window->isOpen())
	{
		sf::Event dummyEvent;
		pollEvents(dummyEvent, false);

		window->clear(); 

		sf::Texture texture; texture.loadFromFile("pic/background.png"); 
		sf::Sprite sprite; sprite.setTexture(texture); 
		window->draw(sprite);

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

	Button instruction("ENTER YOUR NAME: (Press ESC to back to menu)", sf::Vector2f(350, 50), sf::Color::Red, 40, sf::Vector2f(350, 50));
	instruction.setFont(font);
	instruction.setPosition(sf::Vector2f(350, 50));
	Button textBox("     ", sf::Vector2f(125, 140), sf::Color::Red, 40, sf::Vector2f(125, 140));
	textBox.setFont(font);
	textBox.setPosition(sf::Vector2f(125, 140));
	Button enter("LOAD", sf::Vector2f(840, 140), sf::Color::Red, 40, sf::Vector2f(840, 140));
	enter.setFont(font);
	enter.setPosition(sf::Vector2f(840, 140));

	sf::Event event;
	bool submitted = false;
	while (window->isOpen() && !submitted)
	{
		while (pollEvents(event, true)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (enter.mouseClick(*window))
				{
					name = sentence.toAnsiString();
					if (name.length() > 0) {
						submitted = true;
						break;
					}
				}
			}

			int proc = textField(event, sentence);
			if (proc == 1) {
				name = sentence.toAnsiString();
				if (name.length() > 0) {
					submitted = true;
					break;
				}
			}
			if (proc == -1) return show();
			if (proc == 2) text.setString(sentence);
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

	for (int i = 0; i < name.length(); ++i) {
		if (name[i] == ',') name[i] = '.';
	}

	return newGame(loadLevel(name));
}

int Menu::textField(sf::Event event, sf::String &sentence) {
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
			case sf::Keyboard::Escape:
				return -1; // ESC -> back to menu
			// case sf::Keyboard::Return:
			case sf::Keyboard::Enter:
				return 1; // Enter -> Load
			case sf::Keyboard::Backspace:
			case sf::Keyboard::Delete:
				if (sentence.getSize() > 0) sentence.erase(sentence.getSize() - 1);
				return 2;
			default:
				return 0;
		}
	}

	if (event.type == sf::Event::TextEntered) {
		if (32 <= event.text.unicode && event.text.unicode < 126) sentence += (char)event.text.unicode;
		return 2;
	}

	return 0;
	// -1: ESC
	// 0: Nothing
	// 1: submitted
	// 2: text change
}

int Menu::exitGame()
{
	std::cout << "exitGame\n";

	bgMusic = !bgMusic; 
	window->clear();
	sf::Texture texture; texture.loadFromFile("pic/bye.png"); 
	sf::Sprite sprite; sprite.setTexture(texture); 
	window->draw(sprite); 

	sf::Text text; sf::Font font; font.loadFromFile("sugar snow.ttf"); 
	text.setString("good bye"); text.setFillColor(sf::Color::Black); text.setFont(font); 
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
	std::cout << "instruction\n"; 
	sf::Texture texture;
	texture.loadFromFile("pic/background.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);

	sf::Texture texture1; texture1.loadFromFile("pic/awsd.png"); 
	sf::Sprite sprite1; sprite1.setTexture(texture1); 
	sprite1.setScale(sf::Vector2f(0.9f, 0.9f)); 
	sprite1.setPosition(sf::Vector2f(830.0f, 180.0f)); 
	
	std::string line[8] = { "Use A,W,S,D to move the characters avoid the obstacles, ESC to pause.",
						   "When you finish the final level, all of data will reset.",
							"Use mouseclick to choose the options in menu lists.",
							"Turning on/off the music as you want", "Save/Load the game that you may miss.", 
							"GOOD LUCK", "INSTRUCTION", "Press Enter to go back to menu"};
	
	sf::Text text[8]; sf::Font font; font.loadFromFile("Sugar Snow.ttf"); 
	for (int i = 0; i < 8; i++)
	{
		sf::Text *textLine = &text[i];
		textLine->setFont(font);
		textLine->setString(line[i]);
		sf::Color lineColor;
		int lineSize;
		sf::Vector2f linePosition;
		switch (i) {
			case 6:
				lineColor = sf::Color(4, 68, 43);
				lineSize = 50;
				linePosition = sf::Vector2f(500.0f, 80.0f);
				break;
			case 7:
				lineColor = sf::Color::Black;
				lineSize = 40;
				linePosition = sf::Vector2f(300.0f, 600.0f);
				break;
			default:
				lineColor = sf::Color::Red;
				lineSize = 35;
				linePosition = sf::Vector2f(30, 180 + (i + 1) * 50);
		}
		textLine->setFillColor(lineColor);
		textLine->setCharacterSize(lineSize);
		textLine->setPosition(linePosition);
	}

	window->draw(sprite);
	window->draw(sprite1);
	for (int i = 0; i < 8; i++) window->draw(text[i]); 
	window->display();

	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) == false &&  window->isOpen())
	{
		sf::Event event;
		pollEvents(event, false);
	}
	
	return show();
}

int Menu::rank()
{
	std::cout << "rank\n";
	std::ifstream fin;

	std::vector<std::string> info;
	std::vector<int> level;
	fin.open("loadRank.txt", std::ios::in);

	if (fin.is_open())
	{
		std::cout << "can open file\n"; 
		std::string infoLine;
		std::string acc;
		std::string levelStr;
		int l;
		while (std::getline(fin, infoLine))
		{
			if (infoLine == "") continue;
			std::cout << "infoLine.length(): " << infoLine.length() << '\n';
			int i = 0;
			for (; i < infoLine.length(); i++)
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

			if (i == infoLine.length() || l < 0) continue;

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
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && window->isOpen())
	{
		sf::Event event;
		pollEvents(event, false);

		window->clear();
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

	return show();
}

int Menu::show() {
	switch (renderMain())
	{
	case 0:
		return newGame(0);
	case 1:
		return loadGame();
	case 2:
		return rank();
	case 4: 
		return instruction();
	case 5:
		return exitGame();
	default:
		return -1;
	}
}

void Menu::start() {
	show();
}

template <class T>
inline void Menu::swap(T& a, T& b)
{
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}


