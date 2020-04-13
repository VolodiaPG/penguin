#include "MCTSPlayer.hpp"

namespace game
{

MCTSPlayer::MCTSPlayer(game::AbstractGame *game,
    unsigned int id,
    const mcts::MCTSConstraints &constraints)
    : AbstractPlayer(id)
{
    tree = new mcts::Tree(game, this, constraints);
}

AbstractBoardCell * MCTSPlayer::bestMove()
{
    tree->begin();
    return tree->bestMove();
}

void MCTSPlayer::updateTree(AbstractBoardCell* cell)
{
    tree->moveRootToCell(cell);
}

} // namespace game