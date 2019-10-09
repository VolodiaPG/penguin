#include "Position.hpp"

namespace mcts
{
Position::Position()
{
}

Position::Position(int x, int y)
    : Position()
{
    this->x = x;
    this->y = y;
}
} // namespace mcts