#include <iostream>

#include "Board.hpp"

#define PAUSE_TEXT "Please press any key to continue."
#define pause_msg() pause(PAUSE_TEXT)


void print_free_spaces(game::Board &board)
{
	auto ptr_list = board.getEmptyPositions();
	for (const game::Position &pos : *ptr_list)
	{
		std::cout << "(" << pos.x << ", " << pos.y << ")" << std::endl;
	}
}

void print_board(const game::Board &board)
{
	unsigned int index = 0;
	game::boardMatrix boardMatrix = board.getBoardValues();

	for (const game::boardLine &line : boardMatrix)
	{
		for (const game::BoardCell &cell : line)
		{
			const game::Position &pos = cell.getPosition();
			std::cout << cell.getValue() << (pos.y < (unsigned int)line.size() - 1 ? " │ " : "");
		}

		if (index++ < boardMatrix.size() - 1)
		{
			std::cout << std::endl;
			for (unsigned int ii = 0; ii < line.size() - 1; ++ii)
			{
				std::cout << "──┼─" << (ii == (unsigned int)line.size() - 2 ? "─" : "");
			}
		}
		std::cout << std::endl;
	}
}

void print_board_clean_before(const game::Board &board)
{
	// clear the output stdout
	std::cout << "\033c";
	print_board(board);
}

void pause(const char * msg){
	if (msg){
		std::cout << msg << std::endl;
	}
	std::cin.get();
}

int main()
{
	// 3*3 board
	game::Board board = game::Board();
	print_board_clean_before(board);
	pause_msg();

	std::cout << "Move performed" << std::endl;

	board.performMove(1, {2, 2});
	print_board_clean_before(board);
	pause_msg();

	return EXIT_SUCCESS;
}