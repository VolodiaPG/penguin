#include "Tree.hpp"

#include "MCTSPlayer.hpp"

namespace mcts
{

template <class CellT, class PlayerT, class PawnT>
MCTSPlayer<CellT, PlayerT, PawnT>::MCTSPlayer(
    game::AbstractGame<CellT, PlayerT, PawnT> *game,
    game::AbstractPlayer *player,
    const mcts::MCTSConstraints &constraints)
    : _binded_player(player)
{
    tree = new mcts::Tree<CellT, PlayerT, PawnT>(game, constraints);
}

template <class CellT, class PlayerT, class PawnT>
game::Move<CellT, PawnT> MCTSPlayer<CellT, PlayerT, PawnT>::bestMove()
{
    tree->begin();
    return tree->bestMove();
}

template <class CellT, class PlayerT, class PawnT>
void MCTSPlayer<CellT, PlayerT, PawnT>::updateTree(const game::Move<CellT, PawnT> &last_move_played)
{
    tree->moveRootToMove(last_move_played);
}

}