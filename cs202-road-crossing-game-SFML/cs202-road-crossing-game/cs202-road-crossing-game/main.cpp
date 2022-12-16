#include "Game.h"

int main()
{
	Game game; 
	while (game.isRunning() && !game.getEndGame())
	{
		game.update(); 
		game.render(); 
	}
	return 0; 
}