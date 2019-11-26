#include <iostream>

#include "ConsoleGame.hpp"

#include <emscripten/bind.h>
#include <emscripten.h>

using namespace emscripten;

// external function
// extern "C"
// {
// 	extern void test_js(int number);
// }

// Do not include main loop if emscripten is used to compile
#ifndef __EMSCRIPTEN__

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

#endif

int main_emscripten(int test)
{
	std::cout << test << std::endl;

	// test_js(4242);
	EM_ASM_ARGS({
		test_js($0);
	},
				42);

	return 42;
}

EMSCRIPTEN_BINDINGS(module_test)
{
	function("main_emscripten", &main_emscripten);
}
