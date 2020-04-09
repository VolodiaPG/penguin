#include "ConsoleGame.hpp"

namespace game
{
namespace penguin
{
ConsoleGame::ConsoleGame()
    : _game(7, 2),
      _print_hex((Board *)_game.board)
{
    Board *board = (Board *)_game.board;
    // Placing all the penguins
    // team 1
    board->performMove(0, board->getCell(0, 0));
    board->performMove(1, board->getCell(3, 6));
    // team 2
    board->performMove(2, board->getCell(-3, 6));
    board->performMove(3, board->getCell(6, 0));
}

ConsoleGame::~ConsoleGame()
{
}

void ConsoleGame::draw()
{
    _print_hex.print();
}

void ConsoleGame::loop()
{
    std::cout << "looping" << std::endl;
    draw();
    // while (!TicTacToe::isFinished())
    // {

    // }

    // print results
    // if (board->checkStatus() == -1)
    // {
    //     std::cout << "This is a draw :(" << std::endl;
    // }
    // else
    // {
    //     std::cout << "Player #" << board->checkStatus()
    //               << " won!" << std::endl;
    // }
}

} // namespace penguin
} // namespace game