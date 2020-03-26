#include "ConsoleGame.hpp"
#include "../../dbg.h"

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
    int dimension = board.size();

    int offset = 0;
    for (int ii = 0; ii < (int)dimension; ++ii) // ii for the rows
    {
        for (int jj = offset; jj < (int)dimension + offset; ++jj) // jj for the cols
        {
            BoardCell *cell = (BoardCell *)board.getCell(jj, ii);
            std::cout << "(" << cell->getPosition().x << ";" << cell->getPosition().y << ";" << cell->getFish() << ") ";
        }

        if (ii % 2 == 1)
        {
            --offset;
        }
        std::cout << std::endl;
    }

    board.getPlayerById(0)->setStandingOn(board.getCell(1,1));
    dbg(board.getCell(1,1)->getOwner());
    for (auto& cell : board.getAvailableCells(0))
    {
        std::cout << "(" << cell->getPosition().x << ";" << cell->getPosition().y << ") ";   
    }
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