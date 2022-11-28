#include "Header.h"

void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void gotoXY(int x, int y)
{
	COORD coord{};
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void generator(cGame& g)
{
	int delay;
	while (g.IS_RUNNING == true)
	{
		delay = rand() % 1600000000 + 400000000;
		g.obstacleGenerate();
		sleep_for(nanoseconds(delay));
	}
}

void bgWork(cGame& g)
{
	while (g.IS_RUNNING == true)
	{
		g.bgWork();
		g.draw();
		sleep_for(nanoseconds(2000000000));
	}
}