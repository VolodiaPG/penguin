#include <assert.h>

#include "Move.hpp"
#include "AbstractBoardCell.hpp"
#include "AbstractPlayer.hpp"
#include "AbstractPawn.hpp"

#include "tic_tac_toe/Player.hpp"
#include "tic_tac_toe/BoardCell.hpp"

#include "penguin/HumanPlayer.hpp"
#include "penguin/BoardCell.hpp"

namespace game
{

template <class PlayerT, class CellT>
AbstractPawn<PlayerT, CellT>::AbstractPawn(unsigned int id, PlayerT *owner)
    : _id(id),
      _owner(owner)
{
    assert(owner != nullptr);
}

template <class PlayerT, class CellT>
void AbstractPawn<PlayerT, CellT>::makeMove(CellT *cell)
{
    _owner->_moves_done.push({(AbstractBoardCell *)_current_cell,
                              (AbstractBoardCell *)cell,
                              (AbstractPawn<game::AbstractPlayer, game::AbstractBoardCell> *)this});
    _current_cell = cell;
}

template <class PlayerT, class CellT>
CellT *AbstractPawn<PlayerT, CellT>::getCurrentCell() const
{
    return _current_cell;
}

template class AbstractPawn<AbstractPlayer, AbstractBoardCell>;
template class AbstractPawn<tic_tac_toe::Player, tic_tac_toe::BoardCell>;
template class AbstractPawn<penguin::HumanPlayer, penguin::BoardCell>;
} // namespace game