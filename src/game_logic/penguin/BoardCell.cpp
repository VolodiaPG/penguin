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

} // namespace penguin
} // namespace game