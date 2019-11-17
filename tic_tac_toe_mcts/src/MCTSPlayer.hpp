#ifndef MCTS_PLAYER_HPP_
#define MCTS_PLAYER_HPP_

#include "AbstractPlayer.hpp"
#include "AbstractBoard.hpp"
#include "AbstractGame.hpp"
#include "Tree.hpp"

namespace game
{

class MCTSPlayer : public AbstractPlayer
{
protected:
    AbstractGame *game;

public:
    explicit MCTSPlayer(unsigned int id, AbstractGame* game);
    AbstractBoardCell *action(AbstractBoard *board) override;
};

} // namespace game

#endif