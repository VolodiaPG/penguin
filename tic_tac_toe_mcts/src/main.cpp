#include <iostream>

#include "ConsoleGame.hpp"

#define PAUSE_TEXT "Please press any key to continue."
#define pause_msg() pause(PAUSE_TEXT)

void pause(const char *msg)
{
	if (msg)
	{
		std::cout << msg << std::endl;
	}
	std::cin.get();
}

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