#include <iostream>

#include "ConsoleGame.hpp"

int main()
{
		for (int ii = 0; ii < 1; ++ii)
	{
		game::AbstractGame *consoleGame = new game::ConsoleGame();

		consoleGame->loop();

		delete consoleGame;
	}

	return EXIT_SUCCESS;
}