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

bool BoardCell::equals_to(const BoardCell &cell) const
{
    return cell.position == position;
}

} // namespace tic_tac_toe
} // namespace game