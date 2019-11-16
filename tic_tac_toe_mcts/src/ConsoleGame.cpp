#include "ConsoleGame.hpp"

namespace game
{
ConsoleGame::ConsoleGame()
    : AbstractGame(nullptr)
{
    board = new Board();
}

ConsoleGame::~ConsoleGame()
{
    delete board;
}

void ConsoleGame::play()
{
    Board *bo = (Board *)board;
    AbstractPlayer *player = nullptr;

    if (bo->getTotalMoves() % 2 == 0)
    {
        player = &player1;
    }
    else
    {
        player = &player2;
    }

    player->action(board);
}

void ConsoleGame::draw() const
{
    // clear the output stdout
    std::cout << "\033c";

    const std::list<const AbstractBoardCell *> &cells = board->getBoardCells();

    for (const AbstractBoardCell *absCell : cells)
    {
        const BoardCell *cell = (BoardCell *)absCell;
        const Position &pos = cell->getPosition();

        std::cout << cell->getValue() << (pos.y < board->size() - 1 ? " │ " : "");

        // ignore last line
        if (pos.y == board->size() && pos.x != board->size())
        {
            std::cout << std::endl;
            // ignore last column
            for (unsigned int ii = 0; ii < board->size() - 1; ++ii)
            {
                std::cout << "──┼─" << (ii == (unsigned int)board->size() - 2 ? "─" : "");
            }
        }
    }
}

bool ConsoleGame::isFinished() const
{
    return board->checkStatus() != 0;
}
} // namespace game