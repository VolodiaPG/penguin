#include <iostream>
#include "game_logic/penguin/ConsoleGame.hpp"

#ifndef __EMSCRIPTEN__
int main()
{	
	for (int ii = 0; ii < 1; ++ii)
	{
		game::penguin::ConsoleGame consoleGame;

		consoleGame.loop();
	}

	return EXIT_SUCCESS;
}
#endif