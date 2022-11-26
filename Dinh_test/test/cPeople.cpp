#include "cPeople.h"
#include "Header.h"

cPeople::cPeople()
{
	mX = 0;
	mY = 0;
	Level = 1;
}

cPeople::cPeople(int x, int y,int level)
{
	mX = x;
	mY = y;
	Level = level;
}

void cPeople::Up()
{
	if (mY>0) mY--;
}

void cPeople::Left()
{
	if (mX>0) mX--;
}

void cPeople::Right()
{
	if (mX<20) mX++;
}

void cPeople::Down()
{
	if (mY<20) mY++;
}

bool cPeople::printPpl()
{
	gotoXY(mX, mY);
	if (Level == 0)
	{
		std::cout << "d";
		return false;
	}
	std::cout << "p";
	return true;
}

bool cPeople::isImpact(std::vector<obstacle> o)
{
	for (int i = 0; i < o.size(); i++)
	{
		if (mX == o[i].mX)
		{
			Level = 0;
			return true;
		}
	}
	return false;
}