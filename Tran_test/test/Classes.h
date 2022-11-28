#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <utility>
#include <stdio.h>
#include <windows.h>

class obstacle
{
	public:
		int mX=0;
};

class cPeople
{
	int mX, mY;
	int Level; // set level to 0 on collision
	int width, length;
public:
	cPeople();
	cPeople(int x, int y, int level);
	void Up();
	void Left();
	void Right();
	void Down();
	int posX();
	int posY();
	bool printPpl();
	bool isImpact(std::vector<obstacle> o);
	void setMap(int width, int length);
	friend class cGame;
};

class cGame
{
	cPeople player;
	std::vector<std::vector<obstacle>> oVector;
	bool IS_RUNNING = false;
	public:
		void addObstacle(int lane);
		void draw();								//draw map and control player's status
		void gameplay();
		void bgWork();								//control obstacle
		void setLanes();
		void obstacleGenerate();

		friend void generator(cGame& g);
		friend void bgWork(cGame& g);
};