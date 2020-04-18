#ifndef MCTSPLAYER_HPP
#define MCTSPLAYER_HPP

#include "../game_logic/AbstractBoardCell.hpp"
#include "../game_logic/AbstractGame.hpp"
#include "../game_logic/AbstractPlayer.hpp"

#include "../game_logic/tic_tac_toe/BoardCell.hpp"
#include "../game_logic/tic_tac_toe/Player.hpp"

#include "../game_logic/penguin/BoardCell.hpp"
#include "../game_logic/penguin/HumanPlayer.hpp"
#include "../game_logic/penguin/PenguinPawn.hpp"

#include "Tree.hpp"
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

private:
    mcts::Tree<CellT, PlayerT, PawnT> *tree;
};

template class MCTSPlayer<game::tic_tac_toe::BoardCell, game::tic_tac_toe::Player, game::tic_tac_toe::Player>;
template class MCTSPlayer<game::penguin::BoardCell, game::penguin::HumanPlayer, game::penguin::PenguinPawn>;

} // namespace mcts
#endif