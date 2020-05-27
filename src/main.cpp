#include <cstring>
#include <iostream>
#include <time.h> 

#include "game_logic/penguin/ConsoleGame.hpp"
#include "game_logic/tic_tac_toe/ConsoleGame.hpp"

#ifndef NDEBUG
#pragma message("WARNING: `NDEBUG` is not defined, enabling all the debug tools and checks present (assert, etc.)")
#endif

#ifndef __EMSCRIPTEN__
int main(int argn, char **argv)
{
	bool no_print = false;
	if (argn == 2)
	{
			no_print = strcmp("-n", argv[1]) == 0;
	}
	else
 	{
 		std::cout << "Usage: " << argv[0] << " <-n:noprint>" << std::endl;
 	}

 	for (int ii = 0; ii < 1; ++ii)
 	{
 		game::penguin::ConsoleGame consoleGame(no_print);

 		consoleGame.loop();
 	}

 	return EXIT_SUCCESS;
}

#else

int main()
{
	// only for emscipten, likely to be the deployed version
	srand(time(0));

 	return EXIT_SUCCESS;
}

#endif
