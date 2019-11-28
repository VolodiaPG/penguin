#include "MCTSPlayer.hpp"

namespace game
{

MCTSPlayer::MCTSPlayer(unsigned int id, AbstractGame *game)
    : AbstractPlayer(id, game)
{
}

bool MCTSPlayer::action(AbstractBoardCell *)
{
    DEBUG(getId());
    mcts::MCTSConstraints constraints;
    constraints.time = 250;
    mcts::Tree tree(game, this, constraints);
    tree.begin();
    AbstractBoardCell *bestMove = tree.bestMove();

    return AbstractPlayer::action(bestMove);
}
} // namespace game