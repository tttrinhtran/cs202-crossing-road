#include "cPeople.h"
#include "Header.h"

void cGame::addObstacle(int lane)
{
	while (oVector.size() < lane)
	{
		std::vector<obstacle> v;
		oVector.push_back(v);
	}
	obstacle a;
	oVector[lane - 1].push_back(a);
}

void cGame::consoleWork(cPeople player)
{
	int lane = player.mY;
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
}

void cGame::gameplay()
{
	FixConsoleWindow();
	cPeople player;
	char c = 's';
	while (c != (char)27)
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
		consoleWork(player);
		if (player.Level == 0) return;
	}
}