#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <stdio.h>
#include <windows.h>

class obstacle
{
	public:
		int mX=5;
};

class cPeople
{
	int mX, mY;
	int Level; // set level to 0 on collision
public:
	cPeople();
	cPeople(int x, int y, int level);
	void Up();
	void Left();
	void Right();
	void Down();
	bool printPpl();
	bool isImpact(std::vector<obstacle> o);
	friend class cGame;
};

class cGame
{
	std::vector<std::vector<obstacle>> oVector;
	public:
		void addObstacle(int lane);
		void consoleWork(cPeople player);
		void gameplay();
};