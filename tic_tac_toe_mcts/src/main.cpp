#include <emscripten.h>
#include <iostream>

#include "ConsoleGame.hpp"
#include "PlayerVComputer.hpp"
#include "Position.hpp"

// #include <emscripten/bind.h>
// #include <emscripten.h>

// using namespace emscripten;

// int main()
// {
// 	for (int ii = 0; ii < 1; ++ii)
// 	{
// 		game::ConsoleGame consoleGame;

// 		consoleGame.loop();
// 	}

// 	return EXIT_SUCCESS;
// }

extern "C"
{
	EMSCRIPTEN_KEEPALIVE
	game::PlayerVComputer gameInstance;

	EMSCRIPTEN_KEEPALIVE
	int main()
	{
		std::cout << "Hello World" << std::endl;
		// EM_ASM(
		// 	InitWrappers()
		// );
		std::cout << "Initialization Complete" << std::endl;

		return EXIT_SUCCESS;
	}

	EMSCRIPTEN_KEEPALIVE
	void playPlayer1(int row, int col)
	{
		std::cout << "Joué en (" << row << "," << col << ")" << std::endl;
		gameInstance.playPlayer1(row, col);
	}

	EMSCRIPTEN_KEEPALIVE
	int playPlayer2()
	{
		int ret = -1;
		game::BoardCell *cell;

		game::AbstractBoardCell *absCell = gameInstance.playPlayer2();
		if ((cell = dynamic_cast<game::BoardCell *>(absCell)) != nullptr)
		{
			game::Position pos = cell->getPosition();
			ret = pos.x * 3 + pos.y;
		}

		return ret;
	}
}

/* 
Commande pour build mon-site.html :

em++ src/main.cpp -std=c++17 -o morpion.html -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_play', '_main']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall']"
*/
