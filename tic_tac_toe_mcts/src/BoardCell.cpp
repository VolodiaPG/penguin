#include "BoardCell.hpp"

namespace game
{


BoardCell::BoardCell(std::shared_ptr<Position> &position)
    : position(move(position))
{
}

BoardCell::BoardCell()
{
}

int BoardCell::getValue()
{
    return value;
}

int BoardCell::setValue(int value)
{
    this->value = value;
    return this->value;
}

bool BoardCell::isClaimed()
{
    return value;
}

} // namespace game