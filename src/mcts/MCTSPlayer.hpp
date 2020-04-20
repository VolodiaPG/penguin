#ifndef MCTSPLAYER_HPP_
#define MCTSPLAYER_HPP_

#include "../game_logic/AbstractBoardCell.hpp"
#include "../game_logic/AbstractGame.hpp"
#include "../game_logic/AbstractPlayer.hpp"

#include "Tree.hpp"

#define THREAD_NUMBER 1

namespace mcts
{

template <class CellT, class PlayerT, class PawnT>
class MCTSPlayer
{
private:
    game::AbstractPlayer *_binded_player;

public:
    explicit MCTSPlayer(
        game::AbstractGame<CellT, PlayerT, PawnT> *game,
        game::AbstractPlayer *player,
        const mcts::MCTSConstraints &constraints);

    ~MCTSPlayer();

    /**
     * @brief Returns the best move after running the ai
     * 
     * @return AbstractBoardCell* 
     */
    game::Move<CellT, PawnT> bestMove();

    /**
     * @brief Moves the root node to node with targeted cell
     * 
     * @param cell 
     */
    void updateTree(const game::Move<CellT, PawnT> &last_move_played);

protected:
    /**
     * @brief Unleashe the power of the MCTS !!!!
     * @brief Run the mcts multithreaded if num_thread is over 2 or single thread
     * 
     */
    void unleash_mcts();

    // /**
    //  * @brief Get the Corresponding Move object
    //  *
    //  * @param cell
    //  * @return AbstractBoardCell*
    //  */
    const game::Move<CellT, PawnT> getCorrespondingMove(const game::Move<CellT, PawnT>& cell);

    /**
     * @brief Join the multiple trees into 1 so that we can get the best move
     * 
     * @return mcts::Tree 
     */
    mcts::Tree<CellT, PlayerT, PawnT> joinTrees();

    /**
     * @brief Search trees of the MCTSPlayer
     * 
     */
    std::vector<mcts::Tree<CellT, PlayerT, PawnT> *> trees;

    /**
     * @brief Test tree, may be useful for debugging
     * 
     */
    // mcts::Tree<CellT, PlayerT, PawnT> *tree_test;

    /**
     * @brief Current game
     * 
     */
    game::AbstractGame<CellT, PlayerT, PawnT> *game;

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

} // namespace mcts
#endif