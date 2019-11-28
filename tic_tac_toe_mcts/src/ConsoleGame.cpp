#include "ConsoleGame.hpp"

namespace game
{
ConsoleGame::ConsoleGame()
    : TicTacToe(nullptr, nullptr) // instanciate the players afterwards
{
    player1 = new MCTSPlayer(1, this);
    player2 = new MCTSPlayer(2, this);
}

ConsoleGame::~ConsoleGame()
{
    delete player1;
    delete player2;
}

// AbstractBoardCell *ConsoleGame::play(AbstractPlayer *player1, AbstractPlayer *player2)
// {
//     Board *bo = (Board *)board;
//     AbstractPlayer *player = player1;

//     if (bo->getTotalMoves() % 2)
//     {
//         player = player2;
//     }

//     return player->action(board);
// }

void ConsoleGame::draw() const
{
    // clear the output stdout
    // std::cout << "\033c";

    const std::vector<AbstractBoardCell *> &cells = board->getBoardCells();

    for (const AbstractBoardCell *absCell : cells)
    {
        const BoardCell *cell = (BoardCell *)absCell;
        const Position &pos = cell->getPosition();

        std::cout << cell->getValue() << (pos.y < board->size() - 1 ? " │ " : "");

        // ignore last line
        if (pos.y == board->size() - 1 && pos.x < board->size() - 1)
        {
            std::cout << std::endl;
            // ignore last column
            for (unsigned int ii = 0; ii < board->size() - 1; ++ii)
            {
                std::cout << "──┼─" << (ii == (unsigned int)board->size() - 2 ? "─" : "");
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void ConsoleGame::loop()
{
    std::cout << "test" << std::endl;

    draw();
    while (!TicTacToe::isFinished())
    {
        TicTacToe::getNextPlayer()->action(nullptr);
        draw();
    }

    // print results
    if (board->checkStatus() == -1)
    {
        std::cout << "This is a draw :(" << std::endl;
    }
    else
    {
        std::cout << "Player #" << board->checkStatus()
                  << " won!" << std::endl;
    }
}

} // namespace game