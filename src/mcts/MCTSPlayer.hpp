#ifndef MCTSPLAYER_HPP
#define MCTSPLAYER_HPP

#include "../game_logic/AbstractBoardCell.hpp"
#include "../game_logic/AbstractGame.hpp"
#include "Tree.hpp"

namespace game
{

template <class CellT, class PlayerT, class PawnT>
class MCTSPlayer
{
public:
    explicit MCTSPlayer(game::AbstractGame<CellT, PlayerT, PawnT> *game,
                        unsigned int id,
                        const mcts::MCTSConstraints &constraints);

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
    void updateTree(AbstractBoardCell *cell);

private:
    mcts::Tree<CellT, PlayerT, PawnT> *tree;
};

} //namespace game
#endif