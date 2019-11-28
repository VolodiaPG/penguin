#include <iostream>

#include "ConsoleGame.hpp"
#include "PlayerVComputer.hpp"
#include "Position.hpp"

// #include <emscripten/bind.h>
// #include <emscripten.h>

// using namespace emscripten;

int main()
{
	for (int ii = 0; ii < 1; ++ii)
	{
		game::ConsoleGame consoleGame;

		consoleGame.loop();
	}

	return EXIT_SUCCESS;
}
