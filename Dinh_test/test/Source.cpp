#include "Header.h"
#include "cPeople.h"

int main()
{
	cGame g;
	g.addObstacle(5);
	g.addObstacle(10);
	g.addObstacle(15);
	g.gameplay();
	return 0;
}