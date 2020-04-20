#include <assert.h>

#include "tic_tac_toe/Player.hpp"
#include "tic_tac_toe/BoardCell.hpp"
#include "penguin/HumanPlayer.hpp"
#include "penguin/PenguinPawn.hpp"
#include "penguin/BoardCell.hpp"

#include "AbstractPawn.hpp"

namespace game
{

template <class PlayerT, class CellT>
AbstractPawn<PlayerT, CellT>::AbstractPawn(unsigned int id, PlayerT &owner)
    : _id(id),
      _owner(&owner)
{
}

template <class PlayerT, class CellT>
void AbstractPawn<PlayerT, CellT>::setCurrentCell(CellT *cell)
{
    _current_cell = cell;
}

template <class PlayerT, class CellT>
CellT *AbstractPawn<PlayerT, CellT>::getCurrentCell() const
{
    return _current_cell;
}

template <class PlayerT, class CellT>
bool AbstractPawn<PlayerT, CellT>::equals_to(const AbstractPawn<PlayerT, CellT> &pawn) const
{
    bool ret = _id == pawn._id;

    if (ret && _owner != pawn._owner)
        ret = _owner != nullptr && pawn._owner != nullptr && _owner->getId() == pawn._owner->getId();

    if (ret && _current_cell != pawn._current_cell)
        ret = _current_cell != nullptr && pawn._current_cell != nullptr && *_current_cell == *pawn._current_cell;

    return ret;
}

template class AbstractPawn<tic_tac_toe::Player, tic_tac_toe::BoardCell>;
template class AbstractPawn<penguin::HumanPlayer, penguin::BoardCell>;
} // namespace game