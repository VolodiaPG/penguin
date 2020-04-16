#include "tic_tac_toe/Player.hpp"
#include "tic_tac_toe/BoardCell.hpp"

#include "penguin/HumanPlayer.hpp"
#include "penguin/PenguinPawn.hpp"
#include "penguin/BoardCell.hpp"

#include "AbstractPlayer.hpp"

namespace game
{
template<class CellT, class PawnT>
AbstractPlayer<CellT, PawnT>::AbstractPlayer(unsigned int id)
    : id(id)
{
}

template<class CellT, class PawnT >
Move<CellT, PawnT> AbstractPlayer<CellT, PawnT>::dequeueLastMove()
{
    Move<CellT, PawnT> move = _moves_done.top();
    _moves_done.pop();
    move.pawn->_current_cell = move.from;
    return move;
}

template<class CellT, class PawnT>
Move<CellT, PawnT> AbstractPlayer<CellT, PawnT>::getLastMoveDone() const
{
    return _moves_done.top();
}

template class AbstractPlayer<tic_tac_toe::BoardCell, tic_tac_toe::Player>;
template class AbstractPlayer<penguin::BoardCell, penguin::PenguinPawn>;


} // namespace game