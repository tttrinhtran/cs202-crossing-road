#include "Header.h"
#include "classes.h"

int main()
{
	srand(time(NULL));
	cGame g;

	// running game
	g.setLanes();
	std::thread t1(bgWork, std::ref(g));
	std::thread t2(generator, std::ref(g));
	g.gameplay();
	gotoXY(0, 0);
	std::cout << "dead";
	t1.join();
	t2.join();
	// game finished

	return 0;
}