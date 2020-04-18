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
    /**
     * @brief Construct a new MCTSPlayer object
     * 
     * @param game 
     * @param id 
     * @param constraints 
     */
    explicit MCTSPlayer(game::AbstractGame *game, 
                        unsigned int id, 
                        const mcts::MCTSConstraints &constraints);

    /**
     * @brief Destroy the MCTSPlayer object
     * 
     */
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
    /**
     * @brief Unleashe the power of the MCTS !!!!
     * @brief Run the mcts multithreaded if num_thread is over 2 or single thread
     * 
     */
    void unleash_mcts();

    /**
     * @brief Get the Corresponding Move object
     * 
     * @param cell 
     * @return AbstractBoardCell* 
     */
    AbstractBoardCell* getCorrespondingMove(AbstractBoardCell* cell);

    /**
     * @brief Join the multiple trees into 1 so that we can get the best move
     * 
     * @return mcts::Tree 
     */
    mcts::Tree joinTrees();

    /**
     * @brief Search trees of the MCTSPlayer
     * 
     */
    std::vector<mcts::Tree*> trees;

    /**
     * @brief Test tree, may be useful for debugging
     * 
     */
    mcts::Tree* tree_test;

    /**
     * @brief Current game
     * 
     */
    game::AbstractGame *game;

    /**
     * @brief Constraints for the mcts
     * 
     */
    mcts::MCTSConstraints constraints;

    /**
     * @brief Number of threads used by the mcts, default = 1
     * 
     */
    int num_threads = 1;

};

}//namespace game
#endif