#include "../../mcts/MCTSPlayer.hpp"
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
    std::cout << std::endl
              << std::endl;
}

void ConsoleGame::loop()
{
    std::cout << "Looping, wheeeeeeeeeeeeeee!" << std::endl;

    mcts::MCTSConstraints constraints;
    constraints.time = 250;

    mcts::MCTSPlayer<BoardCell, Player, Player> mcts_player_1(this, board->getPlayerById(1), constraints);
    mcts::MCTSPlayer<BoardCell, Player, Player> mcts_player_2(this, board->getPlayerById(2), constraints);

    Move<BoardCell, Player> move;

    draw();
    while (!TicTacToe::isFinished())
    {
        mcts_player_1.updateTree(move);
        mcts_player_2.updateTree(move);

        if (getPlayerToPlay() == 1)
        {
            move = mcts_player_1.bestMove();
        }
        else
        {
            move = mcts_player_2.bestMove();
        }

        play(move.pawn, move.target);
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