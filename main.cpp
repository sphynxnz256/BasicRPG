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
-animator update
	-split animator into controler and individual animation objects

-coins
	-drop animation

-hovering tool tips?

-levels
	-map for level backgrounds
	-vector of file names of textures for enemes and boss for each level
	-multipliers for boss/enemy max hp
	-multiplier for coin drops

-menu screen
	-load game
	-new game
	-options
	-exit etc

-saving games


*/