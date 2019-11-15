#include <iostream>

#include "Board.hpp"

void print_free_spaces(game::Board &board)
{
	auto ptr_list = board.getEmptyPositions();
	for (game::Position pos : *ptr_list)
	{
		std::cout << pos.x << ", " << pos.y << std::endl;
	}
}

int main()
{
	std::cout << "Hello Easy C++ project!" << std::endl;

	// 3*3 board
	game::Board board = game::Board();
	print_free_spaces(board);

	board.performMove(1, {0, 0});
	print_free_spaces(board);

	return EXIT_SUCCESS;
}