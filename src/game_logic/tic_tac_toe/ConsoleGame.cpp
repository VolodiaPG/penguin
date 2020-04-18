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

        std::cout << cell->getValue() << (pos.y < static_cast<int>(board->size()) - 1 ? " │ " : "");

        // ignore last line
        if (pos.y == static_cast<int>(board->size()) - 1 && pos.x < static_cast<int>(board->size()) - 1)
        {
            std::cout << std::endl;
            // ignore last column
            for (unsigned int ii = 0; ii < static_cast<unsigned int>(board->size()) - 1; ++ii)
            {
                std::cout << "──┼─" << (ii == static_cast<unsigned int>(board->size()) - 2 ? "─" : "");
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void ConsoleGame::loop()
{
    std::cout << "Looping, wheeeeeeeeeeeeeee!" << std::endl;

    mcts::MCTSConstraints constraints;
    constraints.time = 250;

    mcts::Tree<BoardCell, Player, Player> tree_1(this, constraints);
    Move<BoardCell, Player> move_1 = {nullptr, nullptr, nullptr};

    mcts::Tree<BoardCell, Player, Player> tree_2(this, constraints);
    Move<BoardCell, Player> move_2 = {nullptr, nullptr, nullptr};

    draw();
    while (!TicTacToe::isFinished())
    {
        const Move<BoardCell, Player>* move;
        if (getPlayerToPlay() == 1)
        {
            tree_1.moveRootToMove(move_1);
            tree_1.begin();
            move_1 = tree_1.bestMove();
            move = &move_1;
        }
        else
        {
            tree_2.moveRootToMove(move_1);
            tree_2.begin();
            move_2 = tree_2.bestMove();
            move = &move_2;
        }
        play(move->pawn, move->target);
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