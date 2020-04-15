#include "Player.hpp"
#include "../AbstractBoard.hpp"
#include "../../mcts/Tree.hpp"

#include "PlayerVComputer.hpp"

namespace game
{
namespace tic_tac_toe
{
PlayerVComputer::PlayerVComputer()
    : TicTacToe()
{
}

PlayerVComputer::~PlayerVComputer()
{
}

bool PlayerVComputer::play(int row, int col)
{
    return play(board->getPlayerById(getPlayerToPlay()), board->getCell(row, col));
}

Move PlayerVComputer::mctsResult()
{
    mcts::MCTSConstraints constraints;
    constraints.time = 250;
    auto game = dynamic_cast<AbstractGame<AbstractBoardCell, AbstractPlayer, AbstractPawn<AbstractPlayer, AbstractBoardCell>> *>(this);
    mcts::Tree tree(game, constraints);
    tree.begin();
    return tree.bestMove();
}
} // namespace tic_tac_toe
} // namespace game
