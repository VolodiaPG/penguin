#include <iostream>

#include "Board.hpp"

using namespace mcts;

void print_free_spaces(Board &board)
{
	auto ptr_list = board.getEmptyPositions();
	for(Position pos : *ptr_list){
		std::cout << pos.x << ", " << pos.y << std::endl;
	}
}

int main()
{
	std::cout << "Hello Easy C++ project!" << std::endl;

	Board board = Board();
	print_free_spaces(board);

	board.performMove(P1, Position(0, 0));
	print_free_spaces(board);

	return EXIT_SUCCESS;
}