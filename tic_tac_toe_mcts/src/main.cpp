#include <iostream>

#include "ConsoleGame.hpp"
#include "PlayerVComputer.hpp"
#include "Position.hpp"

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

game::Position player_action_callback(unsigned int id)
{
	game::Position pos;
	EM_ASM_ARGS({
		$1 = player_action_callback($0);
	},
				id, &pos);
	return pos;
}

int main_emscripten(int test)
{
	std::cout << test << std::endl;

	for (int ii = 0; ii < 1; ++ii)
	{
		game::AbstractGame *game = new game::PlayerVComputer(&player_action_callback);

		game->loop();

		delete game;
	}
	// test_js(4242);
	// EM_ASM_ARGS({
	// 	test_js($0);
	// },
	// 			42);

	return 42;
}

EMSCRIPTEN_BINDINGS(module_test)
{
	class_<game::Position>("Position")
         .constructor<>()
         .property("x", &game::Position::x)
         .property("y", &game::Position::y);

	function("main_emscripten", &main_emscripten);
}
