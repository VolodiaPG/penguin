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

    /**
     * @brief Returns the best move after running the ai
     * 
     * @return AbstractBoardCell* 
     */
    AbstractBoardCell * bestMove();

    /**
     * @brief Moves the root node to node with targeted cell
     * 
     * @param cell 
     */
    void updateTree(AbstractBoardCell* cell);

private:
    mcts::Tree * tree;
};

}//namespace game
#endif