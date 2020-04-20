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

} // namespace penguin
} // namespace game