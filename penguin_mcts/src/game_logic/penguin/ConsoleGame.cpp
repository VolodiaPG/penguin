#include "ConsoleGame.hpp"

namespace game
{
namespace penguin
{
ConsoleGame::ConsoleGame()
    : board(3)
{
}

ConsoleGame::~ConsoleGame()
{
}

void ConsoleGame::draw() const
{
}

void ConsoleGame::loop()
{
    std::cout << "test" << std::endl;

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