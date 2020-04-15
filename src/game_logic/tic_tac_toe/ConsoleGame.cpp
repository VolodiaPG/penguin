#include "ConsoleGame.hpp"

namespace game
{
namespace tic_tac_toe
{
ConsoleGame::ConsoleGame()
    : TicTacToe() // instanciate the players afterwards
{
}

ConsoleGame::~ConsoleGame()
{
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

void ConsoleGame::draw()
{
    // clear the output stdout
    // std::cout << "\033c";

    const std::vector<BoardCell *>
        cells = board->getBoardCells();

    for (const BoardCell *cell : cells)
    {
        const Position &pos = cell->getPosition();

        std::cout << cell->getValue() << (pos.y < (int)board->size() - 1 ? " │ " : "");

        // ignore last line
        if (pos.y == (int)board->size() - 1 && pos.x < (int)board->size() - 1)
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
        mcts::MCTSConstraints constraints;
        constraints.time = 500;
        // auto game = dynamic_cast<AbstractGame<AbstractPlayer, AbstractBoardCell>*>(this);
        auto game = (AbstractGame<AbstractBoardCell, AbstractPlayer, AbstractPawn<AbstractPlayer, AbstractBoardCell>> *)this;
        mcts::Tree tree(game, constraints); // play the second player
        tree.begin();
        Move best_move = tree.bestMove();
        play((Player *)best_move.pawn, (BoardCell *)best_move.target);
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

} // namespace tic_tac_toe
} // namespace game