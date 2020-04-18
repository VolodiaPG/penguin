#include "../AbstractBoardCell.hpp"

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

bool BoardCell::operator==(const BoardCell &cell) const
{
    return cell.position == position;
}

} // namespace penguin
} // namespace game