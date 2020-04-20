#include "PenguinPawn.hpp"

namespace game
{
namespace penguin
{
PenguinPawn::PenguinPawn(unsigned int id, HumanPlayer *owner)
    : AbstractPawn(id, *owner)
{
}

bool PenguinPawn::equals_to(const PenguinPawn &) const
{
    return true;
}
} // namespace penguin
} // namespace game