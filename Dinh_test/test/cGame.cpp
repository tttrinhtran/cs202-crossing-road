#include "Classes.h"
#include "Header.h"

void cGame::addObstacle(int lane)
{
	if (lane - 1 >= player.length) return;
	obstacle a;
	oVector[lane - 1].push_back(a);
}

void cGame::draw()
{
	int lane = player.mY;
	system("cls");
	for (int i = 0; i < oVector.size(); i++)
	{
		for (int k = 0; k < oVector[i].size(); k++)
		{
			gotoXY(oVector[i][k].mX, i);
			std::cout << "o";
		}
	}
	player.isImpact(oVector[lane]);
	player.printPpl();
	if (player.Level == 0)
	{
		IS_RUNNING = false;
		return;
	}
}

void cGame::gameplay()
{
	FixConsoleWindow();
	char c = 's';
	IS_RUNNING = true;
	while (c != (char)27 && IS_RUNNING == true)
	{
		c = _getch();
		switch (c)
		{
		case (char)KEY_UP:
			player.Up();
			break;
		case (char)KEY_DOWN:
			player.Down();
			break;
		case (char)KEY_LEFT:
			player.Left();
			break;
		case (char)KEY_RIGHT:
			player.Right();
			break;
		}
		system("cls");
		draw();
	}
}

void cGame::setLanes()
{
	while (oVector.size() < player.length)
	{
		std::vector<obstacle> lane;
		oVector.push_back(lane);
	}
}

void cGame::bgWork()
{
	for (int i = 0; i < oVector.size(); i++)
	{
		for (int k = 0; k < oVector[i].size(); k++)
		{
			oVector[i][k].mX++;
			if (oVector[i][k].mX == player.width)
			{
				std::swap(oVector[i][k], oVector[i][oVector[i].size() - 1]);
				oVector[i].pop_back();
				k--;
			}
		}
	}
}

void cGame::obstacleGenerate()
{
	int lane = rand() % (player.length - 3) + 2;
	if (oVector[lane].size() > 0)
	{
		if (oVector[lane][oVector[lane].size() - 1].mX > 0)
		{
			addObstacle(lane);
			gotoXY(0, lane-1);
			std::cout << "o";
		}
	}
	else
	{
		addObstacle(lane);
		gotoXY(0, lane-1);
		std::cout << "o";
	}
}