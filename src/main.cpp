#include <iostream>
#include "game_logic/tic_tac_toe/ConsoleGame.hpp"
#include "game_logic/tic_tac_toe/PlayerVComputer.hpp"
#include "game_logic/tic_tac_toe/Position.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
// #include <emscripten/bind.h>
#endif

// using namespace emscripten;
#ifndef __EMSCRIPTEN__
int main()
{	
	for (int ii = 0; ii < 1; ++ii)
	{
		game::ConsoleGame consoleGame;

		consoleGame.loop();
	}

	return EXIT_SUCCESS;
}
#else
extern "C"
{
	// EMSCRIPTEN_KEEPALIVE
	game::PlayerVComputer *gameInstance;

	EMSCRIPTEN_KEEPALIVE
	int main()
	{
		std::cout << "Runtime launched" << std::endl;
		return EXIT_SUCCESS;
	}

	EMSCRIPTEN_KEEPALIVE
	int initGame()
	{
		gameInstance = new game::PlayerVComputer();
		std::cout << "Initialization Complete" << std::endl;

		return EXIT_SUCCESS;
	}

	EMSCRIPTEN_KEEPALIVE
	void deleteGame()
	{
		if (gameInstance)
			delete gameInstance;

		std::cout << "Free Complete" << std::endl;
	}

	EMSCRIPTEN_KEEPALIVE
	int getPlayerToPlay()
	{
		return gameInstance->getPlayerToPlay()->getId();
	}

	EMSCRIPTEN_KEEPALIVE
	int checkStatus()
	{
		return gameInstance->checkStatus();
	}

	EMSCRIPTEN_KEEPALIVE
	void play(int row, int col)
	{
		//std::cout << "Joué en (" << row << "," << col << ")" << std::endl;
		gameInstance->play(row, col);
	}

	EMSCRIPTEN_KEEPALIVE
	int mctsResult()
	{
		std::cout << "Player 2" << std::endl;
		int ret = -1;
		game::BoardCell *cell;

		game::AbstractBoardCell *absCell = gameInstance->mctsResult();
		if ((cell = dynamic_cast<game::BoardCell *>(absCell)) != nullptr)
		{
			game::Position pos = cell->getPosition();
			ret = pos.x * 3 + pos.y;
		}

		return ret;
	}
}
#endif

/* 
Commande pour build mon-site.html :

em++ src/main.cpp -std=c++17 -o morpion.html -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_play', '_main']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall']"

em++ src/AbstractBoard.cpp src/AbstractBoardCell.cpp src/AbstractGame.cpp src/AbstractInterface.cpp src/AbstractPlayer.cpp src/Board.cpp src/BoardCell.cpp src/ConsoleGame.cpp src/log.cpp src/main.cpp src/Node.cpp src/Player.cpp src/PlayerVComputer.cpp src/Position.cpp src/TicTacToe.cpp src/Tree.cpp src/TreeVisualizer.cpp -std=c++17 -o www/main.html --shell-file www/tic-tac-toe.html -s ASSERTIONS=2 -s WASM=1 -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_main', '_initGame', '_deleteGame' ,'_play', '_mctsResult', '_checkStatus', '_getPlayerToPlay']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['cwrap', 'ccall']"
*/
