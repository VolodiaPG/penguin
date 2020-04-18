#include "MCTSPlayer.hpp"

namespace game
{

template <class CellT, class PlayerT, class PawnT>
MCTSPlayer<CellT, PlayerT, PawnT>::MCTSPlayer(game::AbstractGame<CellT, PlayerT, PawnT> *game,
    unsigned int id,
    const mcts::MCTSConstraints &constraints)
{
    tree = new mcts::Tree<CellT, PlayerT, PawnT>(game, this, constraints);
}

template <class CellT, class PlayerT, class PawnT>
AbstractBoardCell * MCTSPlayer<CellT, PlayerT, PawnT>::bestMove()
{
    tree->begin();
    return tree->bestMove();
}

template <class CellT, class PlayerT, class PawnT>
void MCTSPlayer<CellT, PlayerT, PawnT>::updateTree(AbstractBoardCell* cell)
{
    tree->moveRootToCell(cell);
}

} // namespace game