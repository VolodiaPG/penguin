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

std::string BoardCell::to_string() const
{
    return "(x: " + std::to_string(position.x) + ", y:" + std::to_string(position.y) + ")";
}

} // namespace game