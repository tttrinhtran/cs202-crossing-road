#pragma once
#include "Player.h"
#include "Obstacle.h"
#include "Temp.h"
class Game
{
private: 
	sf::RenderWindow* window; 
	sf::VideoMode videoMode; 
	sf::Event event; 

	bool endGame; 
	Player player; 
	/*std::vector <Obstacle> obs; int maxObs; */
	std::vector<Temp> tmp; int maxObs;

	//animation 
	sf::Clock animationTimer; 
	sf::Vector2f curPos; 

	//resource
	sf::Font font;
	sf::Text text; 
	sf::Texture bgTexture;
	sf::Sprite bgSprite; 

	
	// functions 
	void initFont(); 
	void initText(); 
	void initWindow(); 
	void initVariables(); 
	void initBackground(); 
public: 
	Game(); 
	virtual ~Game(); 
	const bool isRunning() const; 
	const bool& getEndGame() const; 
	void pollEvents(); 

	//animation
	void initAnimation(); 
	void spawnObstacle(); 
	void removeObstacle();

	//update
	void updateAnimation(); 
	void updatePlayer();
	void update();

	//render
	void renderBackground(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void render(); 
};