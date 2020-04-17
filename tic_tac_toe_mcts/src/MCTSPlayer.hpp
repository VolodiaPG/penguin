#ifndef MCTSPLAYER_HPP
#define MCTSPLAYER_HPP

#include "AbstractPlayer.hpp"
#include "Tree.hpp"
#include "AbstractBoardCell.hpp"
#include "AbstractGame.hpp"
#include "mcts.hpp"

#include <thread>
#include <functional>

namespace game
{

class MCTSPlayer : public AbstractPlayer
{
public:

    explicit MCTSPlayer(game::AbstractGame *game, 
                        unsigned int id, 
                        const mcts::MCTSConstraints &constraints);

    ~MCTSPlayer();
    
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

protected:
    void unleash_mcts();
    AbstractBoardCell* getCorrespondingMove(AbstractBoardCell* cell);
    mcts::Tree joinTrees();

private:
    std::vector<mcts::Tree*> trees;
    mcts::Tree* tree_test;
    game::AbstractGame *game;
    mcts::MCTSConstraints constraints;
    int num_threads = 1;

};

}//namespace game
#endif