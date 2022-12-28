#include "Menu.h"

int main() {
	Menu menu;
	switch (menu.renderMain())
	{
	case 0:
		menu.newGame();
		break;
	case 1:
		menu.loadGame();
		break;
	case 2:
		menu.rank();
		break;
	case 4:
		menu.exitGame();
		break;
	default:
		break;
	}

	return 0;
}