#include <assert.h>

#include "tic_tac_toe/Player.hpp"
#include "tic_tac_toe/BoardCell.hpp"

#include "penguin/HumanPlayer.hpp"
#include "penguin/PenguinPawn.hpp"
#include "penguin/BoardCell.hpp"

#include "AbstractBoard.hpp"

namespace game
{
template <class CellT, class PlayerT, class PawnT>
bool AbstractBoard<CellT, PlayerT, PawnT>::performMove(PawnT *pawn, CellT *cell)
{
    if (pawn)
    {
        _history.enqueue({pawn->getCurrentCell(),
                          cell,
                          pawn});
        pawn->setCurrentCell(cell);
    }

    return pawn != nullptr;
}

template <class CellT, class PlayerT, class PawnT>
const Move<CellT, PawnT> AbstractBoard<CellT, PlayerT, PawnT>::revertMove()
{
    assert("Cannot dequeue, empty stack" && _history.size() > 0);
    const Move<CellT, PawnT> &move = _history.dequeue();
    move.pawn->setCurrentCell(move.from);
    return move;
}

template class AbstractBoard<tic_tac_toe::BoardCell, tic_tac_toe::Player, tic_tac_toe::Player>;
template class AbstractBoard<penguin::BoardCell, penguin::HumanPlayer, penguin::PenguinPawn>;
} // namespace game
