#include <iostream>
#include "game_logic/penguin/ConsoleGame.hpp"
#include "game_logic/tic_tac_toe/ConsoleGame.hpp"

#ifndef NDEBUG
#pragma message("WARNING: `NDEBUG` is not defined, enabling all the debug tools and checks present (assert, etc.)") 
#endif

#ifndef __EMSCRIPTEN__
int main()
{	
	for (int ii = 0; ii < 1; ++ii)
	{
		game::penguin::ConsoleGame consoleGame;

		consoleGame.loop();
	}
	// for (int ii = 0; ii < 1; ++ii)
	// {
	// 	game::tic_tac_toe::ConsoleGame consoleGame;

	// 	consoleGame.loop();
	// }

	return EXIT_SUCCESS;
}
#endif