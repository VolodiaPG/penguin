#ifndef MCTSPLAYER_HPP
#define MCTSPLAYER_HPP

#include "AbstractPlayer.hpp"
#include "Tree.hpp"
#include "AbstractBoardCell.hpp"
#include "AbstractGame.hpp"

namespace game
{

class MCTSPlayer : public AbstractPlayer
{
public:

    explicit MCTSPlayer(game::AbstractGame *game, 
                        unsigned int id, 
                        const mcts::MCTSConstraints &constraints);
    AbstractBoardCell * bestMove();
    void updateTree(AbstractBoardCell &cell);

private:
    mcts::Tree * tree;
};

}//namespace game
#endif