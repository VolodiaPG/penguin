#include "ConsoleGame.hpp"

namespace game
{
namespace penguin
{
ConsoleGame::ConsoleGame()
    : _board(7, 4),
      _print_hex(&_board)
{
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