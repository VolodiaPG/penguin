#include "BoardCell.hpp"

namespace game
{
namespace tic_tac_toe
{

BoardCell::BoardCell(const Position &position)
    : position(position)
{
}

int BoardCell::getValue() const
{
    return value;
}

int BoardCell::setValue(int value)
{
    this->value = value;
    return this->value;
}

bool BoardCell::isClaimed() const
{
    return value;
}

bool BoardCell::equals_to(const AbstractBoardCell &cell) const
{
    const BoardCell *ce = dynamic_cast<const BoardCell *>(&cell);
    bool ret = ce != nullptr;

    if (ret)
    {
        ret = ce->position == position;
    }

    return ret;
}

} // namespace tic_tac_toe
} // namespace game