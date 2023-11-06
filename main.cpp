#include "stdafx.h"
#include "Game.h"

int main()
{
	//initiate random seed
	srand(static_cast<unsigned>(time(0)));

	Game game;

	//main game loop
	while (game.getWindow().isOpen())
	{
		game.update();
		game.render();
	}

	return 0;
}