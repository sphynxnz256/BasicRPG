#include "stdafx.h"
#include "Game.h"

int main()
{
	//create a reusable random number generator
	RNG rng;

	Game game(rng);

	//main game loop
	while (game.getWindow().isOpen())
	{
		game.update();
		game.render();
	}

	return 0;
}

/*to do

-coins
	-drop animation
	-pick up coins?

-levels
	-everything has more hp
	-new enemies
	-more loots

-saving games

-menu screen
	-load game
	-new game
	-exit etc
*/