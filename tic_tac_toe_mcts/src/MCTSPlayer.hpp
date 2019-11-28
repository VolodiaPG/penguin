#ifndef MCTS_PLAYER_HPP_
#define MCTS_PLAYER_HPP_

#include "AbstractPlayer.hpp"
#include "AbstractBoard.hpp"
#include "AbstractGame.hpp"
#include "Tree.hpp"
#include "TreeVisualizer.hpp"

namespace game
{

class MCTSPlayer : public AbstractPlayer
{
public:
    explicit MCTSPlayer(unsigned int id, AbstractGame* game);
    bool action(AbstractBoardCell *cell) override;
};

} // namespace game

#endif