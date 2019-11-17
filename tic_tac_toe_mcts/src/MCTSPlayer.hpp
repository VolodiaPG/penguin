#ifndef MCTS_PLAYER_HPP_
#define MCTS_PLAYER_HPP_

#include "AbstractPlayer.hpp"
#include "AbstractBoard.hpp"

namespace game
{

class MCTSPlayer : public AbstractPlayer
{
public:
    void action(AbstractBoard *board) override;
};

} // namespace game

#endif