#include "../../mcts/Tree.hpp"
#include "Board.hpp"
#include "BoardCell.hpp"

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
        mcts::Tree<BoardCell, Player, Player> tree(this, constraints); // play the second player
        tree.begin();
        Move<BoardCell, Player> best_move = tree.bestMove();
        play(static_cast<Player *>(best_move.pawn), best_move.target);
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