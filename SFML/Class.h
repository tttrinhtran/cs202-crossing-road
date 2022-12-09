//
// Created by PGTHINH on 08/12/2022.
//

#ifndef CROSSING_CLASS_H
#define CROSSING_CLASS_H
#include "Header.h"

class Player{ 
	int xPos, yPos;
	int level;
	sf::Sprite rect;
public: 
	int getLevel()
	{
		return level;
	}
	sf::Sprite &getRect()
	{
		return rect; 
	}
	Player(float x, float y, std::string str, int posX, int posY, int level)
	{
		sf::Texture santa;
		santa.loadFromFile("pic/"+str+".png");
		rect.setTexture(santa);
		rect.setScale(x, y);
		this->xPos = posX;
		this->yPos = posY; 
		this->level = level;
		rect.setPosition(xPos, yPos);
	}
	bool Pass(sf::Sprite& lane)
	{
		if (lane.getGlobalBounds().contains(rect.getPosition().x, rect.getPosition().y))
			return true;
		else return false; 
	}
};

class Obstacles 
{
protected: 
	sf::Sprite obs; 
	int xPos, speed, lane, yPos;
public: 
	sf::Sprite& getRect()
	{
		return obs;
	}
	Obstacles(std::string str, int posX, int posY, int s, int l, float x, float y)
	{
		this->xPos = posX; 
		this->yPos = posY; 
		this->speed = s;
		this->lane = l; 
		sf::Texture santa;
		santa.loadFromFile("pic/" + str + ".png");
		obs.setTexture(santa);
		obs.setScale(x, y);
		obs.setPosition(xPos, yPos);
	}

	void moveLeft()
	{
		for (int i = 0; i < 5; i++)
		{
			std::this_thread::sleep_for(std::chrono::nanoseconds(100000000));
			obs.move(10.f, 0.f);
		}
	}
};
#endif //CROSSING_CLASS_H
