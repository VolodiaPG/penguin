#include "ConsoleGame.hpp"

namespace game
{
namespace penguin
{
ConsoleGame::ConsoleGame()
    : board(7, 4)
{
}

ConsoleGame::~ConsoleGame()
{
}

void ConsoleGame::draw()
{
    // dbg(board.getCell(1,1)->getOwner());
    board.getPlayerById(0)->setStandingOn(board.getCell(1,1));
    board.getCell(1,1)->setOwner(board.getPlayerById(0));
    // dbg(board.getCell(1,1)->getOwner());

    PrintHex print_hex(board.size());
    print_hex.print(board);
    
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