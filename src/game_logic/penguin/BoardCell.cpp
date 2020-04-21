#include "../AbstractBoardCell.hpp"
#include "PenguinPawn.hpp"
#include "Board.hpp"

#include "BoardCell.hpp"

namespace game
{
namespace penguin
{
BoardCell::BoardCell(const Position &position, unsigned int number_fish)
    : position(position),
      _number_fish(number_fish)
{
}

bool BoardCell::equals_to(const AbstractBoardCell &cell) const
{
    const BoardCell *ce = dynamic_cast<const BoardCell *>(&cell);
    bool ret = ce != nullptr;

    if (ret)
        ret = ce->position == position;
    if (ret && ce->_owner != _owner)
        ret = ce->_owner != nullptr && _owner != nullptr && ce->_owner->getId() == _owner->getId();

    return ret;
}

BoardCell *BoardCell::clone(const Board *const &board) const
{
    BoardCell *ret = new BoardCell(position, _number_fish);
    if (isOwned())
    {
        ret->_owner = board->getPawnById(getOwner()->getId());
    }
    ret->_gone = _gone;
    return ret;
} // namespace penguin

} // namespace penguin
} // namespace game