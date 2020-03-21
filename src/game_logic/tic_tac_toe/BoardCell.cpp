#include "BoardCell.hpp"

namespace game
{

// BoardCell::BoardCell()
// {
// }

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

} // namespace game